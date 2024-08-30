#include <assert.h>
#include <d3d11.h>

#include "Pipeline.h"

#if not defined _DEBUG
#define MUST(Expression) (      (         (Expression)))
#else
#define MUST(Expression) (assert(SUCCEEDED(Expression)))
#endif

namespace Pipeline
{
    namespace
    {
        ID3D11Device        * Device;
        ID3D11DeviceContext * DeviceContext;

        IDXGISwapChain * SwapChain;

        namespace Buffer
        {
            ID3D11Buffer * Vertex;
            ID3D11Buffer * Constant[2];
        }

        ID3D11RenderTargetView * RenderTargetView;
    }

    void Create(ID3D11ShaderResourceView *& view, SIZE const & size, BYTE const * const data)
    {
        D3D11_TEXTURE2D_DESC const Descriptor
        {
            static_cast<UINT>(size.cx),
            static_cast<UINT>(size.cy),
            1,
            1,
            DXGI_FORMAT_B8G8R8A8_UNORM,
            1,
            0,
            D3D11_USAGE_IMMUTABLE,
            D3D11_BIND_SHADER_RESOURCE
        };

        UINT const BPP = 32;

        D3D11_SUBRESOURCE_DATA const Subresource
        {
            data,
            size.cx * (BPP / 8)
        };

        ID3D11Texture2D * Texture2D = nullptr;
        
        MUST(Device->CreateTexture2D(&Descriptor, &Subresource, &Texture2D));

        ID3D11ShaderResourceView * ShaderResourceView = nullptr;

        MUST(Device->CreateShaderResourceView(Texture2D, nullptr, &view));
    }

    void Render(ID3D11ShaderResourceView * const & view, RECT const & area)
    {
        DeviceContext->PSSetShaderResources(0, 1, &view);
        {
            D3D11_MAPPED_SUBRESOURCE Subresource = D3D11_MAPPED_SUBRESOURCE();

            MUST(DeviceContext->Map(Buffer::Vertex, 0, D3D11_MAP_WRITE_DISCARD, 0, &Subresource));
            {
                float const Coordinates[4][2]
                {
                    { static_cast<float>(area.left),  static_cast<float>(area.top)    },
                    { static_cast<float>(area.right), static_cast<float>(area.top)    },
                    { static_cast<float>(area.left),  static_cast<float>(area.bottom) },
                    { static_cast<float>(area.right), static_cast<float>(area.bottom) }
                };

                memcpy_s(Subresource.pData, Subresource.RowPitch, Coordinates, sizeof(Coordinates));
            }
            DeviceContext->Unmap(Buffer::Vertex, 0);
        }
        DeviceContext->Draw(4, 0);
    }

    void Delete(ID3D11ShaderResourceView * const & view)
    {
        view->Release();
    }

    namespace Transform
    {
        template<Type type>
        void Update(LPCVOID const matrix)
        {
            UINT constexpr index = static_cast<UINT>(type);
        
            D3D11_MAPPED_SUBRESOURCE Subresource = D3D11_MAPPED_SUBRESOURCE();
        
            MUST(DeviceContext->Map(Buffer::Constant[index], 0, D3D11_MAP_WRITE_DISCARD, 0, &Subresource));
            {
                memcpy_s(Subresource.pData, Subresource.RowPitch, matrix, Subresource.RowPitch);
            }
            DeviceContext->Unmap(Buffer::Constant[index], 0);
        }
        
        template void Update<Type::Former>(LPCVOID const);
        template void Update<Type::Latter>(LPCVOID const);
    }

    void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
    {
        switch(uMessage)
        {
            case WM_CREATE:
            {
                {
                    DXGI_SWAP_CHAIN_DESC Descriptor = DXGI_SWAP_CHAIN_DESC();
                    
                    Descriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                    Descriptor.SampleDesc.Count  = 1;
                    Descriptor.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                    Descriptor.BufferCount       = 1;
                    Descriptor.OutputWindow      = hWindow;
                    Descriptor.Windowed          = true;
                    Descriptor.Flags             = DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE;

                    MUST(D3D11CreateDeviceAndSwapChain
                    (
                        nullptr,
                        D3D_DRIVER_TYPE_HARDWARE,
                        nullptr,
                        D3D11_CREATE_DEVICE_SINGLETHREADED,
                        nullptr,
                        0,
                        D3D11_SDK_VERSION,
                        &Descriptor,
                        &SwapChain,
                        &Device,
                        nullptr,
                        &DeviceContext
                    ));
                }
                {
                    #include "Shader/Bytecode/Vertex.h"
                    {
                        D3D11_INPUT_ELEMENT_DESC const Descriptor[]
                        {
                            { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0 },
                            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1 }
                        };

                        ID3D11InputLayout * InputLayout = nullptr;

                        MUST(Device->CreateInputLayout
                        (
                            Descriptor,
                            _ARRAYSIZE(Descriptor),
                            Bytecode,
                            sizeof(Bytecode),
                            &InputLayout
                        ));

                        DeviceContext->IASetInputLayout(InputLayout);

                        InputLayout->Release();
                    }
                    {
                        ID3D11VertexShader * VertexShader = nullptr;
                        
                        MUST(Device->CreateVertexShader
                        (
                            Bytecode,
                            sizeof(Bytecode),
                            nullptr,
                            &VertexShader
                        ));
                        
                        DeviceContext->VSSetShader(VertexShader, nullptr, 0);

                        VertexShader->Release();
                    }
                }
                {
                    #include "Shader/Bytecode/Pixel.h"
                    {
                        ID3D11PixelShader * PixelShader = nullptr;

                        MUST(Device->CreatePixelShader
                        (
                            Bytecode,
                            sizeof(Bytecode),
                            nullptr,
                            &PixelShader
                        ));

                        DeviceContext->PSSetShader(PixelShader, nullptr, 0);

                        PixelShader->Release();
                    }
                }
                {
                    DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
                }
                {
                    float const Coordinates[4][2]
                    {
                        { -0.5f, +0.5f }, { +0.5f, +0.5f },
                        { -0.5f, -0.5f }, { +0.5f, -0.5f }
                    };

                    D3D11_BUFFER_DESC const Descriptor
                    {
                        sizeof(Coordinates),
                        D3D11_USAGE_IMMUTABLE,
                        D3D11_BIND_VERTEX_BUFFER,
                        0
                    };

                    D3D11_SUBRESOURCE_DATA const Subresource { Coordinates };

                    ID3D11Buffer * Buffer = nullptr;

                    MUST(Device->CreateBuffer(&Descriptor, &Subresource, &Buffer));

                    UINT const Stride = sizeof(*Coordinates);
                    UINT const Offset = 0;

                    DeviceContext->IASetVertexBuffers(0, 1, &Buffer, &Stride, &Offset);

                    Buffer->Release();
                }
                {
                    D3D11_BUFFER_DESC const Descriptor
                    {
                        sizeof(float[4][2]),
                        D3D11_USAGE_DYNAMIC,
                        D3D11_BIND_VERTEX_BUFFER,
                        D3D11_CPU_ACCESS_WRITE
                    };

                    MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Vertex));

                    UINT const Stride = sizeof(float[2]);
                    UINT const Offset = 0;

                    DeviceContext->IASetVertexBuffers(1, 1, &Buffer::Vertex, &Stride, &Offset);
                }
                {
                    D3D11_BUFFER_DESC const Descriptor
                    {
                        sizeof(float[4][4]),
                        D3D11_USAGE_DYNAMIC,
                        D3D11_BIND_CONSTANT_BUFFER,
                        D3D11_CPU_ACCESS_WRITE
                    };

                    for(UINT i = 0; i < _ARRAYSIZE(Buffer::Constant); ++i)
                        MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Constant[i]));

                    DeviceContext->VSSetConstantBuffers(0, _ARRAYSIZE(Buffer::Constant), Buffer::Constant);
                }
                {
                    ID3D11BlendState * BlendState = nullptr; 

                    D3D11_BLEND_DESC Descriptor = D3D11_BLEND_DESC();
                     
                    Descriptor.RenderTarget->BlendEnable           = true;
                    Descriptor.RenderTarget->SrcBlend              = D3D11_BLEND_SRC_ALPHA;
                    Descriptor.RenderTarget->DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
                    Descriptor.RenderTarget->BlendOp               = D3D11_BLEND_OP_ADD;
                    Descriptor.RenderTarget->SrcBlendAlpha         = D3D11_BLEND_ZERO;
                    Descriptor.RenderTarget->DestBlendAlpha        = D3D11_BLEND_ONE;
                    Descriptor.RenderTarget->BlendOpAlpha          = D3D11_BLEND_OP_ADD;
                    Descriptor.RenderTarget->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

                    Device->CreateBlendState(&Descriptor, &BlendState);

                    DeviceContext->OMSetBlendState(BlendState, nullptr, D3D11_DEFAULT_SAMPLE_MASK);

                    BlendState->Release();
                }

                return;
            }
            case WM_APP:
            {
                MUST(SwapChain->Present(0, 0));

                float const Color[4] { 0.0f, 0.0f, 0.0f, 1.0f };

                DeviceContext->ClearRenderTargetView(RenderTargetView, Color);

                return;
            }
            case WM_DESTROY:
            {
                DeviceContext->ClearState();

                RenderTargetView->Release();

                for(UINT i = 0; i < _ARRAYSIZE(Buffer::Constant); ++i)
                    Buffer::Constant[i]->Release();

                Buffer::Vertex->Release();

                SwapChain->Release();

                DeviceContext->Release();
                Device->Release();

                return;
            }
            case WM_SIZE:
            {
                {
                    D3D11_VIEWPORT const Viewport
                    {
                        0.0f, 
                        0.0f,
                        static_cast<float>(LOWORD(lParameter)),
                        static_cast<float>(HIWORD(lParameter))
                    };

                    DeviceContext->RSSetViewports(1, &Viewport);
                }
                {
                    if(RenderTargetView != nullptr)
                    {
                        RenderTargetView->Release(); 

                        MUST(SwapChain->ResizeBuffers
                        (
                            1,
                            LOWORD(lParameter),
                            HIWORD(lParameter),
                            DXGI_FORMAT_B8G8R8A8_UNORM,
                            DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE
                        ));
                    }
                    {
                        ID3D11Texture2D * Texture2D = nullptr;

                        MUST(SwapChain->GetBuffer(0, IID_PPV_ARGS(&Texture2D)));
                        {
                            MUST(Device->CreateRenderTargetView(Texture2D, nullptr, &RenderTargetView));
                        }
                        Texture2D->Release();

                        DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
                    }
                }

                return;
            }
        }
    }
}
#include <Windows.h>

#include <map>
#include <string>

#include "Resource.h"

#include "Pipeline.h"
#include "FreeImage.h"
#include "Rendering.h"

namespace Pipeline { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }

namespace Rendering
{
    namespace
    {
        inline auto S(float const w, float const h)
        {
            return Matrix<4>
            {
                w, 0, 0, 0,
                0, h, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1,
            };
        }

        inline auto R(float const & r)
        {
            return Matrix<4>
            {
                cosf(r), sinf(r), 0, 0,
               -sinf(r), cosf(r), 0, 0,
                    (0),     (0), 1, 0,
                    (0),     (0), 0, 1,
            };
        }

        inline auto T(float const x, float const y)
        {
            return Matrix<4>
            {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                x, y, 0, 1,
            };
        }

        std::map<std::string const, std::pair<ID3D11ShaderResourceView * const , SIZE const> const> Views;

        //map은 RB Tree로 시간복잡도 = O(nlogn) 가짐
        //map 의 first와 second로 std::string const, std::pair 2개 가짐
        //그리고 pair에서 ID3D11ShaderResourceView * const , SIZE const 이 두개를 first와second로 가짐


        void Import(std::string const & file)
        {
            FIBITMAP * bitmap = FreeImage_Load(FreeImage_GetFileType(file.data()), file.data());
            {
                if(FreeImage_GetBPP(bitmap) != 32)
                {
                    FIBITMAP * const previous = bitmap;

                    bitmap = FreeImage_ConvertTo32Bits(bitmap);

                    FreeImage_Unload(previous);
                }

                FreeImage_FlipVertical(bitmap);
            }
            {
                ID3D11ShaderResourceView * view = nullptr;
                {
                    SIZE const size
                    {
                        static_cast<LONG>(FreeImage_GetWidth(bitmap)),
                        static_cast<LONG>(FreeImage_GetHeight(bitmap))
                    };

                    BYTE const * const data = FreeImage_GetBits(bitmap);

                    Pipeline::Create(view, size, data);
                }
                {
                    SIZE const size
                    {
                        static_cast<LONG>(FreeImage_GetWidth(bitmap)),
                        static_cast<LONG>(FreeImage_GetHeight(bitmap))
                    };

                    UINT const start = static_cast<UINT>(file.find_first_of('/') + sizeof(char));
                    UINT const end   = static_cast<UINT>(file.find_last_of('.'));

                    Views.try_emplace(file.substr(start, end - start), std::make_pair(view, size));
                }
            }
            FreeImage_Unload(bitmap);
        }
    }

    void Component::Render()
    {
        {
            Matrix<4> const matrix = S(Length[0], Length[1]) * R(Angle) * T(Location[0], -Location[1]);

            Pipeline::Transform::Update<Pipeline::Transform::Type::Former>(&matrix);
        }
        {
            std::pair<ID3D11ShaderResourceView * const, SIZE const> const & pair = Views.at(Content);

            RECT const area
            {
                             0,              0,
                pair.second.cx, pair.second.cy,
            };

            Pipeline::Render(pair.first, area);
        }
    }

    void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
    {
        switch(uMessage)
        {
            case WM_CREATE:
            {
                Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

                FreeImage_Initialise();
                {
                    Resource::Import("Image", Import);
                }
                FreeImage_DeInitialise();

                return;
            }
            case WM_APP:
            {
                Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

                return;
            }
            case WM_DESTROY:
            {
                for (auto & pair : Views)
                    Pipeline::Delete(pair.second.first);

                Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

                return;
            }
            case WM_SIZE:
            {
                Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

                Matrix<4> const matrix = S(2.0f / LOWORD(lParameter), 2.0f / HIWORD(lParameter)) * T(-1, 1);

                Pipeline::Transform::Update<Pipeline::Transform::Type::Latter>(&matrix);

                return;
            }
        }
    }
}
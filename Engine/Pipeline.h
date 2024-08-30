#pragma once

struct ID3D11ShaderResourceView;

namespace Pipeline
{
    void Create(ID3D11ShaderResourceView *       & view, SIZE const & size, BYTE const * const data);
    void Render(ID3D11ShaderResourceView * const & view, RECT const & area);
    void Delete(ID3D11ShaderResourceView * const & view);

    namespace Transform
    {
        enum class Type { Former, Latter };

        template<Type type>
        void Update(LPCVOID const matrix);
    }
}
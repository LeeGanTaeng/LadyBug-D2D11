#pragma once

template<int m, int n = m>
class Matrix final
{
    friend class Matrix;

public:
    template<typename... Type>
    Matrix(Type const &... element) : element { static_cast<float>(element)... }
    {
        static_assert(not (m == 1 and n == 1), "Matrix<1, 1> cannot be created.");
    }

    auto operator +(void) const
    {
        return *this;
    }

    auto operator +(Matrix<m, n> const & other) const
    {
        Matrix<m, n> product = *this;

        for(int u = 0; u < m; ++u)
            for(int v = 0; v < n; ++v)
                product.element[u][v] += other.element[u][v];

        return product;
    }

    auto & operator +=(Matrix<m, n> const & other)
    {
        return *this = *this + other;
    }

    auto operator *(float const & other) const
    {
        Matrix<m, n> product = *this;

        for(int u = 0; u < m; ++u)
            for(int v = 0; v < n; ++v)
                product.element[u][v] *= other;

        return product;
    }

    auto & operator *=(float const & other)
    {
        return *this = *this * other;
    }

    auto operator -(void) const
    {
        return *this * -1;
    }

    auto operator -(Matrix<m, n> const & other) const
    {
        return *this + (-other);
    }

    auto & operator -=(Matrix<m, n> const & other)
    {
        return *this = *this - other;
    }

    auto operator /(float const & other) const
    {
        return *this * (1 / other);
    }

    auto & operator /=(float const & other)
    {
        return *this = *this / other;
    }

    template<int l>
    auto operator *(Matrix<n, l> const & other) const
    {
        if constexpr (m == 1 and l == 1)
        {
            float product = float();

            for(int u = 0; u < n; ++u)
                product += (*this).element[0][u] * other.element[u][0];

            return product;
        }
        else
        {
            Matrix<m, l> product = Matrix<m, l>();

            for(int u = 0; u < m; ++u)
                for(int v = 0; v < l; ++v)
                    for(int w = 0; w < n; ++w)
                        product.element[u][v] += (*this).element[u][w] * other.element[w][v];

            return product;
        }
    }

    auto & operator *=(Matrix<n, n> const & other)
    {
        return *this = *this * other;
    }

    auto & operator [](int const & index)
    {
             if constexpr (m != 1 and n == 1) return (*( element)[index]);
        else if constexpr (m == 1 and n != 1) return ( (*element)[index]);
        else if constexpr (m != 1 and n != 1) return ( ( element)[index]);
    }

    auto & operator [](int const & index) const
    {
        return (*const_cast<Matrix<m, n> *>(this))[index];
    }

private:
    float element[m][n];
};

template<unsigned m, unsigned n>
inline auto operator *(float const & one, Matrix<m, n> const & other)
{
    return other * one;
}

template<unsigned m, unsigned n>
inline auto operator /(float const & one, Matrix<m, n> const & other)
{
    return other / one;
}
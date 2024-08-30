#pragma once

template<size_t m, size_t n = m>
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

        for(size_t i = 0; i < m; ++i)
            for(size_t j = 0; j < n; ++j)
                product.element[i][j] += other.element[i][j];

        return product;
    }

    auto & operator +=(Matrix<m, n> const & other)
    {
        return *this = *this + other;
    }

    auto operator *(float const & other) const
    {
        Matrix<m, n> product = *this;

        for(size_t i = 0; i < m; ++i)
            for(size_t j = 0; j < n; ++j)
                product.element[i][j] *= other;

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

    template<size_t l>
    auto operator *(Matrix<n, l> const & other) const
    {
        if constexpr (m == 1 and l == 1)
        {
            float product = float();

            for(size_t i = 0; i < n; ++i)
                product += (*this).element[0][i] * other.element[i][0];

            return product;
        }
        else
        {
            Matrix<m, l> product = Matrix<m, l>();

            for(size_t i = 0; i < m; ++i)
                for(size_t j = 0; j < l; ++j)
                    for(size_t k = 0; k < n; ++k)
                        product.element[i][j] += (*this).element[i][k] * other.element[k][j];

            return product;
        }
    }

    auto & operator *=(Matrix<n, n> const & other)
    {
        return *this = *this * other;
    }

    auto & operator [](size_t const & index)
    {
             if constexpr (m != 1 and n == 1) return (*( element)[index]);
        else if constexpr (m == 1 and n != 1) return ( (*element)[index]);
        else if constexpr (m != 1 and n != 1) return ( ( element)[index]);
    }

    auto & operator [](size_t const & index) const
    {
        return const_cast<Matrix<m, n> &>(*this)[index];
    }

private:
    float element[m][n];
};

template<size_t m, size_t n>
inline auto operator *(float const & one, Matrix<m, n> const & other)
{
    return other * one;
}
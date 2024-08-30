#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

#include "Matrix.h"

template<size_t n>
using Vector = Matrix<1, n>;

template<size_t n>
inline float Dot(Vector<n> const & one, Vector<n> const & other)
{
    return one * reinterpret_cast<Matrix<n, 1> const &>(other);
}

template<size_t n>
inline float Length(Vector<n> const & one)
{
    return sqrtf(Dot(one, one));
}

template<size_t n>
inline Vector<n> Normalize(Vector<n> const & one)
{
    return one / Length(one);
}

inline Vector<3> Cross(Vector<3> const & one, Vector<3> const & other)
{
    Vector<3> product = Vector<3>();

    for(size_t i = 0; i < 3; ++i)
    {
        size_t j = (i + 1) % 3;
        size_t k = (j + 1) % 3;

        product[i] = one[j] * other[k] - one[k] * other[j];
    }

    return product;
}
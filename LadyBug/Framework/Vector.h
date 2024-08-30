#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

#include "Matrix.h"

template<int n>
using Vector = Matrix<1, n>;

template<int n>
inline float Dot(Vector<n> const & one, Vector<n> const & other)
{
    return one * reinterpret_cast<Matrix<n, 1> const &>(other);
}

template<int n>
inline float Length(Vector<n> const & one)
{
    return sqrtf(Dot(one, one));
}

template<int n>
inline Vector<n> Normalize(Vector<n> const & one)
{
    return one / Length(one);
}

inline Vector<3> Cross(Vector<3> const & one, Vector<3> const & other)
{
    Vector<3> product = Vector<3>();

    for(int u = 0; u < 3; ++u)
    {
        int v = (u + 1) % 3;
        int w = (v + 1) % 3;

        product[u] = one[v] * other[w] - one[w] * other[v];
    }

    return product;
}
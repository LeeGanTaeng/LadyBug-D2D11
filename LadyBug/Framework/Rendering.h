#pragma once

#include "Vector.h"

namespace Rendering
{
    class Component final
    {
    public:
        void Render();

    public:
        char const * Content { nullptr };

    public:
        Vector<2> Location { 0.0f, 0.0f };
        Vector<2> Length   { 0.0f, 0.0f };
        float     Angle    { 0.0f };
    };
}
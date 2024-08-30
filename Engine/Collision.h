#pragma once

#include <functional>

#include "Vector.h"

namespace Collision
{
    enum class Group { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z };

    class Component final
    {
    public:
         Component(Group const group = Collision::Group::Z);
        ~Component();

    public:
        bool
        Activated { false };

        std::function<void(Collision::Group const group)>
        Event { nullptr };

    private:
        Collision::Group const
        Group { 0 };

    public:
        float
        Radius { 0.0f };
        
        Vector<2>
        Location { 0.0f, 0.0f };
    };
}
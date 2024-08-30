#pragma once

#include "Framework/Rendering.h"

class Object abstract
{
public:
    virtual ~Object() = default;

    virtual void Update() abstract;

    virtual void Render()
    {
        Skin->Render();
    };

protected:
    Rendering::Component * Skin = nullptr;
};
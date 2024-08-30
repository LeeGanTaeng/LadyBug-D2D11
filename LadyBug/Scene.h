#pragma once

#include "Object.h"

class Scene : public Object
{
public:
    Scene();

    void Update() override;
    void Render() override;

private:
    float const Speed = { 25.0f };
};
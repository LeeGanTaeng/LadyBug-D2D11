#pragma once

#include "Skill.h"

class Cosmos2 : public Skill
{
public:
    Cosmos2();

    void Validate(Vector<2> const & location) override;

    void Update() override;
    void Render() override;

private:
    static int const Count = { 7 };

    float const Speed = { 300.0f };
};
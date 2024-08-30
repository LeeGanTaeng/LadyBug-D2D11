#pragma once

#include "Skill.h"

class Bee : public Skill
{
public:
    Bee();

    void Validate(Vector<2> const & location) override;

    void Update() override;
    void Render() override;

private:
    float const Speed    = { 25.0f };
    float       Current  = { 0.0f };
    float const Duration = { 0.1f };
};
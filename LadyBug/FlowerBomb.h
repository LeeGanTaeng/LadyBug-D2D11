#pragma once

#include "Skill.h"

class FlowerBomb : public Skill
{
public:
    FlowerBomb();

    void Validate(Vector<2> const & location) override;

    void Update() override;
    void Render() override;

private:
    float       Current  = { 0.0f };
    float const Duration = { 7.5f };
};
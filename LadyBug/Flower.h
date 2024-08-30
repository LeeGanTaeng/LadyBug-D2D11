#pragma once

#include "Skill.h"

class Flower : public Skill
{
public:
    Flower(Vector<2> const & player);

    void Validate(Vector<2> const & location) override;

    void Update() override;
    void Render() override;

private:
    Vector<2> const & Player;

    float       Current  = { 0.0f };
    float const Limit    = { 7.5f };
};
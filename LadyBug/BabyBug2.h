#pragma once

#include "Skill.h"

class BabyBug2 : public Skill
{
public:
    BabyBug2(Vector<2> const & player);

    void Validate(Vector<2> const & location) override;

    void Update() override;
    void Render() override;

private:
    static int const Count = { 15 };

    Vector<2>   const & Player;
    Vector<2> * const   Directions;

    float const Speed   = { 300.0f };
    float       Current = { 0.0f };
    float const Limit   = { 0.03125f * Count };
};
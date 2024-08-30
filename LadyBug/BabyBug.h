#pragma once

#include "Skill.h"

class BabyBug : public Skill
{
public:
    BabyBug(Vector<2> const & player);

    void Validate(Vector<2> const & location) override;

    void Update() override;
    void Render() override;

private:
    static int const Count = { 15 };

    Rendering::Component * const Ammo;

    Vector<2>   const & Player;
    Vector<2> * const   Velocities;

    float       Current = { 0.0f };
    float const Limit   = { 0.125f * Count };
};
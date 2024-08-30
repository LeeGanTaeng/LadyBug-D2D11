#pragma once

#include "Skill.h"

class Cosmos : public Skill
{
public:
    Cosmos(Vector<2> const & player);

    void Validate(Vector<2> const & location) override;

    void Update() override;
    void Render() override;

private:
    static int const Count = { 8 };

    Vector<2>   const & Player;
    Vector<2> * const   Distances;

    float        Current = { 0.0f };
    float  const Limit   = { 5.5f };
    float  const Speed   = { 200.0f };
};
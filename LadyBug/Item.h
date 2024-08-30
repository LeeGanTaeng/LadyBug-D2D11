#pragma once

#include "Actor.h"

class Item final : public Actor
{
public:
    Item(Skill * const content);

    void Validate(Vector<2> const & location) override;

    void Update() override;
    void Render() override;

private:
    void OnCollided(Collision::Group const group);

private:
    Actor * const Content;
    Vector<2>     Direction;

    int const Speed     = { 100 };
    bool      Activated = { false };
};
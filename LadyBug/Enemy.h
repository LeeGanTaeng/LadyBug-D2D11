#pragma once

#include "Actor.h"

class Enemy : public Actor
{
public:
    Enemy(Vector<2> const & player);

    void Validate(Vector<2> const & location) override;

    void Update() override;
    void Render() override;

private:
    void OnCollided(Collision::Group const group);

private:
    Vector<2> const & Player;
    Vector<2>         Direction;
    int               Speed;
};
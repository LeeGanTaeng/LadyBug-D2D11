#pragma once

#include "Actor.h"

class Player : public Actor
{
public:
    Player();

    Vector<2> const & GetLocation() const;

    void Validate(Vector<2> const & location) override;

    void Update() override;
    void Render() override;

private:
    void OnCollided(Collision::Group const group);
};
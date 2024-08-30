#include "Framework/Collision.h"
#include "Framework/Random.h"
#include "Framework/Rendering.h"
#include "Framework/Time.h"
#include "Framework/Vector.h"

#include "Enemy.h"

Enemy::Enemy(Vector<2> const & player) : Player(player)
{
    Body = new Collision::Component(Collision::Group::C);

    Body->Event  = std::bind(&Enemy::OnCollided, this, std::placeholders::_1);
    Body->Radius = 32;

    Skin = new Rendering::Component;

    Skin->Content = "Character/Enemy";
    Skin->Length  = Body->Radius * 2 * Vector<2>(1, 1);
}

void Enemy::Validate(Vector<2> const & location)
{
    Direction = Normalize(Player + Vector<2>(Random::GetFloat(-100, 100), 0) - location);
    Speed     = Random::GetInt(50, 150);

    Body->Activated = true;
    Body->Location  = location - Vector<2>(0, Body->Radius);

    Skin->Angle    = acosf(Dot(Vector<2>(0, -1), Direction)) * (Direction[0] < 0 ? 1 : -1);
    Skin->Location = Body->Location;

    Valid = true;
}

void Enemy::Update()
{
    Skin->Location = Body->Location += Time::GetDelta() * Speed * Direction;

    if ((Body->Location[0] <= -Body->Radius) or (600 + Body->Radius <= Body->Location[0]) or (900 + Body->Radius <= Body->Location[1]))
        Valid = false;
}

void Enemy::Render()
{
    Skin->Render();
}

void Enemy::OnCollided(Collision::Group const group)
{
    if (group == Collision::Group::Z)
        Valid = Body->Activated = false;
}
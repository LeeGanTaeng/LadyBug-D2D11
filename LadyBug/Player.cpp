#include "Framework/Collision.h"
#include "Framework/Input.h"
#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "Player.h"

Player::Player()
{
    Body = new Collision::Component(Collision::Group::A);

    Body->Event  = std::bind(&Player::OnCollided, this, std::placeholders::_1);
    Body->Radius = 32;

    Skin = new Rendering::Component;

    Skin->Content = "Character/Player";
    Skin->Length  = Body->Radius * 2 * Vector<2>(1, 1);
}

Vector<2> const & Player::GetLocation() const
{
    return Body->Location;
}

void Player::Validate(Vector<2> const & location)
{
    Body->Activated = true;
    Body->Location  = location - Vector<2>(0, Body->Radius);

    Skin->Location = Body->Location;

    Valid = true;
}

void Player::Update()
{
    Vector<2> const destination = Vector<2>(Input::GetCursorX(), Input::GetCursorY());

    if (destination[0] != 0 or destination[1] != 0)
    {
        Vector<2> const velocity = Vector<2>(Input::GetCursorX(), Input::GetCursorY()) - Skin->Location;

        Skin->Angle    = acos(Dot(Vector<2>(0, -1), Normalize(velocity))) * (velocity[0] < 0 ? 1 : -1);
        Skin->Location = Body->Location += Time::GetDelta() * velocity;
    }
}

void Player::Render()
{
    Skin->Render();
}

void Player::OnCollided(Collision::Group const group)
{
    if (group == Collision::Group::C)
        Valid = Body->Activated = false;
}
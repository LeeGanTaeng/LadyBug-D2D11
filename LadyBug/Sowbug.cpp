#include "Framework/Collision.h"
#include "Framework/Input.h"
#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "Sowbug.h"

Sowbug::Sowbug(Vector<2> const & player) : Skill(Skill::Type::Sowbug), Player(player)
{
    Body = new Collision::Component;

    Body->Radius = 80;

    Skin = new Rendering::Component;

    Skin->Content = "Skill/Sowbug";
    Skin->Length  = Body->Radius * 2 * Vector<2>(1, 1);
}

void Sowbug::Validate(Vector<2> const & location)
{
    Velocity = Vector<2>(Input::GetCursorX(), Input::GetCursorY()) - Player;
    Count    = 0;
    Current  = 0;

    Body->Activated = true;
    Body->Location  = location;

    Skin->Angle    = 0;
    Skin->Location = Body->Location;

    Valid = true;
}

void Sowbug::Update()
{
    Skin->Location = Body->Location += Time::GetDelta() * Velocity;

    if (Count < 5)
    {
        if ((Body->Location[0] <= 0 + Body->Radius) or (600 - Body->Radius <= Body->Location[0]))
        {
            Velocity[0] = -Velocity[0];

            Count += 1;
        }

        if ((Body->Location[1] <= 0 + Body->Radius) or (900 - Body->Radius <= Body->Location[1]))
        {
            Velocity[1] = -Velocity[1];
            
            Count += 1;
        }
    }
    else if
    (
        (Body->Location[0] <= -Body->Radius) or (600 + Body->Radius <= Body->Location[0]) or
        (Body->Location[1] <= -Body->Radius) or (900 + Body->Radius <= Body->Location[1])
    )
    {
        Valid = Body->Activated = false;
    }

    if (Limit <= (Current += Time::GetDelta()))
        Valid = Body->Activated = false;
}

void Sowbug::Render()
{
    Skin->Angle += Time::GetDelta() * static_cast<float>(M_PI) * 2;

    Skin->Render();
}
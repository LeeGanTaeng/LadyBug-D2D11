#include "Framework/Collision.h"
#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "Bee.h"

Bee::Bee() : Skill(Skill::Type::Bee)
{
    Body = new Collision::Component;

    Body->Radius = 80;

    Skin = new Rendering::Component;

    Skin->Length = Body->Radius * 2 * Vector<2>(1, 1);
}

void Bee::Validate(Vector<2> const & location)
{
    Body->Activated = true;
    Body->Location  = location;

    Skin->Location = Skin->Location;

    Valid = true;

    Update();
}

void Bee::Update()
{
    Skin->Location = Body->Location += Time::GetDelta() * Speed * Vector<2>(0, -1);

    if (Body->Location[1] <= -Body->Radius)
        Valid = Body->Activated = false;
}

void Bee::Render()
{
    if(Current < Duration / 2) Skin->Content = "Skill/Bee/Former";
    else                       Skin->Content = "Skill/Bee/Latter";

    if (Current < Duration) Current += Time::GetDelta();
    else                    Current  = fmod(Current, Duration);

    Skin->Render();
}
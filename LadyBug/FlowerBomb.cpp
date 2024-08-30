#include "Framework/Collision.h"
#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "FlowerBomb.h"

FlowerBomb::FlowerBomb() : Skill(Skill::Type::FlowerBomb)
{
    Body = new Collision::Component;

    Body->Radius = 128;

    Skin = new Rendering::Component;

    Skin->Content = "Skill/FlowerBomb";
    Skin->Length  = Body->Radius * 2 * Vector<2>(1, 1);
}

void FlowerBomb::Validate(Vector<2> const & location)
{
    Current = 0;

    Body->Activated = true;
    Body->Location  = location;
    
    Skin->Angle    = 0;
    Skin->Location = Body->Location;

    Valid = true;

    Update();
}

void FlowerBomb::Update()
{
    if (Duration <= (Current += Time::GetDelta()))
        Valid = Body->Activated = false;
}

void FlowerBomb::Render()
{
    Skin->Angle += Time::GetDelta() * static_cast<float>(M_PI);

    Skin->Render();
}
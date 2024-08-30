#include "Framework/Collision.h"
#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "Flower.h"

Flower::Flower(Vector<2> const & player) : Skill(Skill::Type::Flower), Player(player)
{
    Body = new Collision::Component;

    Skin = new Rendering::Component;

    Skin->Content = "Skill/Flower";
}

void Flower::Validate(Vector<2> const & location)
{
    Body->Activated = true;
    Body->Radius    = 96;

    Skin->Length = Body->Radius * 2 * Vector<2>(1, 1);
    Skin->Angle  = 0;

    Current = 0;

    Valid = true;

    Update();
}

void Flower::Update()
{
    Skin->Location = Body->Location = Player;

    if (Limit <= (Current += Time::GetDelta()))
        Valid = Body->Activated = false;
}

void Flower::Render()
{
    Skin->Angle += Time::GetDelta() * static_cast<float>(M_PI);

    Skin->Render();
}
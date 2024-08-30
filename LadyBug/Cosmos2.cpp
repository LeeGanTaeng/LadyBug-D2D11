#include "Framework/Collision.h"
#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "Cosmos2.h"

Cosmos2::Cosmos2() : Skill(Skill::Type::Cosmos2)
{
    Body = new Collision::Component[Count];

    for (int i = 0; i < Count; ++i)
    {
        Body[i].Radius      = 32;
        Body[i].Location[0] = (600 - Body[i].Radius * 2 * Count) / 2 + Body[i].Radius * (2 * i + 1);
    }

    Skin = new Rendering::Component[Count];

    for (int i = 0; i < Count; ++i)
    {
        Skin[i].Content     = "Skill/Cosmos";
        Skin[i].Length      = Body[i].Radius * 2 * Vector<2>(1, 1);
        Skin[i].Location[0] = Body[i].Location[0];
    }
}

void Cosmos2::Validate(Vector<2> const & location)
{
    for (int i = 0; i < Count; ++i)
    {
        Body[i].Activated   = true;
        Body[i].Location[1] = 900 + Body[i].Radius;

        Skin[i].Angle       = 0;
        Skin[i].Location[1] = Body[i].Location[1];
    }

    Valid = true;

    Update();
}

void Cosmos2::Update()
{
    for (int i = 0; i < Count; ++i)
        Skin[i].Location = Body[i].Location += Time::GetDelta() * Speed * Vector<2>(0, -1);

    if (Body[0].Location[1] <= -Body[0].Radius)
        for (int i = 0; i < Count; ++i)
            Valid = Body[i].Activated = false;
}

void Cosmos2::Render()
{
    for (int i = 0; i < Count; ++i)
    {
        Skin[i].Angle += Time::GetDelta() * static_cast<float>(M_PI) * 2;

        Skin[i].Render();
    }
}
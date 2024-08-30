#include "Framework/Collision.h"
#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "Cosmos.h"

Cosmos::Cosmos(Vector<2> const & player)
    : Skill(Skill::Type::Cosmos)
    , Player(player)
    , Distances(new Vector<2>[Count])
{
    Body = new Collision::Component[Count];

    for (int i = 0; i < Count; ++i)
        Body[i].Radius = 32;

    Skin = new Rendering::Component[Count];

    float const delta  = static_cast<float>(M_PI) * 2 / Count;
    float const radius = 96;
    float       radian = 0;

    for (int i = 0; i < Count; ++i)
    {
        Skin[i].Content = "Skill/Cosmos";
        Skin[i].Length  = Body[i].Radius * 2 * Vector<2>(1, 1);

        Distances[i] = radius / sqrtf(static_cast<float>(1 + i % 2)) * Vector<2>(cosf(radian), sinf(radian));
        
        radian += delta;
    }
}

void Cosmos::Validate(Vector<2> const & location)
{
    Current = 0;

    for (int i = 0; i < Count; ++i)
    {
        Body[i].Activated = true;

        Skin[i].Angle = 0;
    }

    Valid = true;

    Update();
}

void Cosmos::Update()
{
    if (Limit <= (Current += Time::GetDelta()))
    {
        for (int i = 0; i < Count; ++i)
            Skin[i].Location = Body[i].Location += Time::GetDelta() * Speed * Vector<2>(0, -1);
    }
    else
    {
        for (int i = 0; i < Count; ++i)
            Skin[i].Location = Body[i].Location = Player + Distances[i];
    }

    Valid = false;

    for (int i = 0; i < Count; ++i)
        Valid |= Body[i].Activated = (-Body[i].Radius < Body[i].Location[1]);
}

void Cosmos::Render()
{
    for (int i = 0; i < Count; ++i)
    {
        Skin[i].Angle += Time::GetDelta() * static_cast<float>(M_PI) * 2;

        Skin[i].Render();
    }
}
#include "Framework/Collision.h"
#include "Framework/Input.h"
#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "BabyBug.h"

BabyBug::BabyBug(Vector<2> const & player)
    : Skill(Skill::Type::BadyBug)
    , Ammo(new Rendering::Component[Count])
    , Player(player)
    , Velocities(new Vector<2>[Count])
{
    Body = new Collision::Component[Count];

    for (int i = 0; i < Count; ++i)
        Body[i].Radius = 16;

    Skin = new Rendering::Component[Count];

    for (int i = 0; i < Count; ++i)
    {
        Skin[i].Content = "Skill/BabyBug/Bullet";
        Skin[i].Length  = Body[i].Radius * 2 * Vector<2>(1, 1);

        Ammo[i].Content = "Skill/BabyBug/Ammo";
        Ammo[i].Length  = Body[i].Radius * Vector<2>(1.5f, 0.75f);
        Ammo[i].Angle   = static_cast<float>(M_PI) / 2;
    }
}

void BabyBug::Validate(Vector<2> const & location)
{
    Current = 0;

    for (int i = 0; i < Count; ++i)
        Body[i].Activated = true;

    Valid = true;

    Update();
}

void BabyBug::Update()
{
    Valid = false;

    for (int i = 0; i < Count; ++i)
    {
        if (Limit / Count * i < Current)
        {
            Skin[i].Location = Body[i].Location += Time::GetDelta() * Velocities[i];
        }
        else
        {
            Velocities[i] = Vector<2>(Input::GetCursorX(), Input::GetCursorY()) - Player;

            if (Length(Velocities[i]) < 200)
                Velocities[i] = Normalize(Velocities[i]) * 200;

            Skin[i].Location = Body[i].Location = Player;
            Skin[i].Angle    = acos(Dot(Vector<2>(0, -1), Normalize(Velocities[i]))) * (Velocities[i][0] < 0 ? +1 : -1);

            Ammo[i].Location = Player + Vector<2>(Ammo[i].Length[1] * Count / 2 - Ammo[i].Length[1] * i, Ammo[i].Length[0] / 2 + Body[i].Radius * 2 + 5);
        }

        if
        (
            (Body[i].Location[0] <= -Body[i].Radius) or (600 + Body[i].Radius <= Body[i].Location[0]) or
            (Body[i].Location[1] <= -Body[i].Radius) or (900 + Body[i].Radius <= Body[i].Location[1])
        )
        {
            Body[i].Activated = false;
        }

        Valid |= Body[i].Activated;
    }

    Current += Time::GetDelta();
}

void BabyBug::Render()
{
    for (int i = 0; i < Count; ++i)
    {
        if (Limit / Count * i <= Current)
        {
            if(Body[i].Activated == true)
                Skin[i].Render();
        }
        else
        {
            Ammo[i].Render();
        }
    }
}
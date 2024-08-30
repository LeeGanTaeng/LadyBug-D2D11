#include "Framework/Collision.h"
#include "Framework/Input.h"
#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "BabyBug2.h"

BabyBug2::BabyBug2(Vector<2> const & player)
    : Skill(Skill::Type::BadyBug2)
    , Player(player)
    , Directions(new Vector<2>[Count])
{
    Body = new Collision::Component[Count];

    for (int i = 0; i < Count; ++i)
        Body[i].Radius = 16;

    Skin = new Rendering::Component[Count];

    for (int i = 0; i < Count; ++i)
    {
        Skin[i].Content = "Skill/BabyBug/Bullet";
        Skin[i].Length  = Body[i].Radius * 2 * Vector<2>(1, 1);
    }
}

void BabyBug2::Validate(Vector<2> const & location)
{
    Current = 0;

    float const delta = static_cast<float>(M_PI) * 2 / 15;
    float       angle = static_cast<float>(M_PI) / 2 + acos(Dot(Vector<2>(0, -1), Normalize(Vector<2>(Input::GetCursorX(), Input::GetCursorY()) - Player)));

    for (int i = 0; i < Count; ++i)
    {
        Directions[i] = Vector<2>(cosf(angle), -sinf(angle));
        
        angle -= delta;

        Body[i].Activated = true;
        Body[i].Location  = Player;

        Skin[i].Angle    = acos(Dot(Vector<2>(0, -1), Directions[i])) * (Directions[i][0] < 0 ? +1 : -1);
        Skin[i].Location = Body[i].Location;
    }

    Valid = true;

    Update();
}

void BabyBug2::Update()
{
    Valid = false;

    for (int i = 0; i < Count; ++i)
    {
        if (Limit / Count * i < Current) Skin[i].Location = Body[i].Location += Time::GetDelta() * Speed * Directions[i];
        else                             Skin[i].Location = Body[i].Location  = Player;

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

void BabyBug2::Render()
{
    for (int i = 0; i < Count; ++i)
        if (Limit / Count * i < Current and Body[i].Activated == true)
            Skin[i].Render();
}
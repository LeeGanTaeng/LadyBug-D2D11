#include "Framework/Collision.h"
#include "Framework/Random.h"
#include "Framework/Rendering.h"
#include "Framework/Random.h"
#include "Framework/Time.h"

#include "Skill.h"
#include "Item.h"

Item::Item(Skill * const content) : Content(content)
{
    Body = new Collision::Component(Collision::Group::B);

    Body->Event  = std::bind(&Item::OnCollided, this, std::placeholders::_1);
    Body->Radius = 32;

    Skin = new Rendering::Component;

    switch (content->GetType())
    {
        case Skill::Type::Flower:     Skin->Content = "Item/Flower";     break;
        case Skill::Type::FlowerBomb: Skin->Content = "Item/FlowerBomb"; break;
        case Skill::Type::Bee:        Skin->Content = "Item/Bee";        break;
        case Skill::Type::BadyBug:    Skin->Content = "Item/BadyBug";    break;
        case Skill::Type::BadyBug2:   Skin->Content = "Item/BadyBug2";   break;
        case Skill::Type::Cosmos:     Skin->Content = "Item/Cosmos";     break;
        case Skill::Type::Cosmos2:    Skin->Content = "Item/Cosmos2";    break;
        case Skill::Type::Sowbug:     Skin->Content = "Item/Sowbug";     break;
    }

    Skin->Length = Body->Radius * 2 * Vector<2>(1, 1);
}

void Item::Validate(Vector<2> const & location)
{
    Direction = Normalize(Vector<2>(Random::GetFloat(-150, 150), 450));

    Body->Activated = true;
    Body->Location  = location - Vector<2>(0, Body->Radius);

    Skin->Location = Body->Location;

    Valid = true;
}

void Item::Update()
{
    if (Activated == false)
    {
        Body->Location = Skin->Location += Time::GetDelta() * Speed * Direction;

        if ((Body->Location[0] <= Body->Radius) or (600 - Body->Radius <= Body->Location[0]))
            Direction[0] = -Direction[0];

        if (900 - Body->Radius <= Body->Location[1])
            Direction[1] = -Direction[1];

        if (Body->Location[1] <= -Body->Radius * 2)
            Valid = Body->Activated = false;
    }
    else
    {
        Content->Update();

        if (Content->GetValid() == false)
            Activated = Valid = false;
    }
}

void Item::Render()
{
    if (Activated == false) Skin->Render();
    else                    Content->Render();
}

void Item::OnCollided(Collision::Group const group)
{
    if (group == Collision::Group::A)
    {
        Body->Activated = false;

        Activated = true;

        Content->Validate(Body->Location);
    }
}
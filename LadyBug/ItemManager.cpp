#include "Framework/Random.h"

#include "Skill.h"
#include "FlowerBomb.h"
#include "Bee.h"
#include "SowBug.h"
#include "Cosmos2.h"
#include "Cosmos.h"
#include "Flower.h"
#include "BabyBug2.h"
#include "BabyBug.h"

#include "Item.h"
#include "ItemManager.h"

ItemManager::ItemManager(Vector<2> const & player) : Player(player)
{
    for (int i = 0; i < Count; ++i) Actors.push_back(new Item(new FlowerBomb));
    for (int i = 0; i < Count; ++i) Actors.push_back(new Item(new Bee));
    for (int i = 0; i < Count; ++i) Actors.push_back(new Item(new Sowbug(player)));
    for (int i = 0; i < Count; ++i) Actors.push_back(new Item(new Cosmos2));
    for (int i = 0; i < Count; ++i) Actors.push_back(new Item(new Cosmos(player)));
    for (int i = 0; i < Count; ++i) Actors.push_back(new Item(new Flower(player)));
    for (int i = 0; i < Count; ++i) Actors.push_back(new Item(new BabyBug2(player)));
    for (int i = 0; i < Count; ++i) Actors.push_back(new Item(new BabyBug(player)));
    
    Spawn();
}

void ItemManager::Update()
{
    Interval = 5;

    Manager::Update();
}

void ItemManager::Spawn()
{
    bool spawned = false;

    do
    {
        int const type = Random::GetInt
        (
            static_cast<int>(Skill::Type::FlowerBomb),
            static_cast<int>(Skill::Type::BadyBug)
        );

        for (int i = type * Count; i < (type + 1) * Count; ++i)
        {
            if (Actors[i]->GetValid() == false)
            {
                Actors[i]->Validate(Vector<2>(Random::GetFloat(150, 450), 0));

                spawned = true;

                break;
            }
        }
    }
    while (spawned == false);
}
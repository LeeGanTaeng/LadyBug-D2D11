#include "Framework/Random.h"
#include "Framework/Vector.h"

#include "Enemy.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(Vector<2> const & player) : Player(player), Count(5)
{
    Actors.reserve(255);

    for (int i = 0; i < 255; ++i)
        Actors.push_back(new Enemy(Player));

    Spawn();
}

void EnemyManager::Update()
{
    Count = 5;// + static_cast<int>(Time::GetElapsed() / 10);
    Interval = 5;

    Manager::Update();
}

void EnemyManager::Spawn()
{
    int current = 0;

    for (Actor * const actor : Actors)
    {
        if (actor->GetValid() == false)
        {
            actor->Validate(Vector<2>(Random::GetFloat(0, 600), 0));

            current += 1;

            if(Count <= current)
                break;
        }
    }
}
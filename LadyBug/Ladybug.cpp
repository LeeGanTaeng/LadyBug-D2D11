#include "Scene.h"
#include "Player.h"
#include "ItemManager.h"
#include "EnemyManager.h"
#include "Ladybug.h"

void Ladybug::Start()
{
    player = new Player;

    player->Validate(Vector<2>(300, 900));
    
    scene         = new Scene;
    item_manager  = new ItemManager(player->GetLocation());
    enemy_manager = new EnemyManager(player->GetLocation());
}

bool Ladybug::Update()
{
    scene->Update();
    scene->Render();

     item_manager->Update();
    enemy_manager->Update();

    if (player->GetValid() == true)
    {
        player->Update();
        player->Render();
    }

    return true;
}

void Ladybug::End()
{
    delete enemy_manager;
    delete item_manager;
    delete scene;
    delete player;
}
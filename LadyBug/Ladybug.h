#pragma once

#include "Framework/Game.h"

class Scene;
class Player;
class EnemyManager;
class SkillManager;
class ItemManager;

class Ladybug : public Game
{
public:
    void  Start() override;
    bool Update() override;
    void    End() override;

private:
    Scene        * scene         { nullptr };
    Player       * player        { nullptr };
    ItemManager  * item_manager  { nullptr };
    SkillManager * skill_manager { nullptr };
    EnemyManager * enemy_manager { nullptr };
};
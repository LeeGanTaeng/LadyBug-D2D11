#pragma once

#include "Manager.h"

class EnemyManager : public Manager
{
public:
    EnemyManager(Vector<2> const & player);

    void Update() override;

private:
    void Spawn() override;

private:
    Vector<2> const & Player;
    int            Count;
};
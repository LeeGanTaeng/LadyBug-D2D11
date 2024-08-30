#pragma once

#include "Manager.h"

class ItemManager : public Manager
{
public:
    ItemManager(Vector<2> const & player);

    void Update() override;

private:
    void Spawn() override;

private:
    static int const Count = { 5 };

    Vector<2> const & Player;
};
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "./Library/FreeImage.lib")
#pragma comment(lib, "./Library/Framework.lib")

#include "Game.h"

#include "../Ladybug.h"

Game * Game::Initialize()
{
    return new Ladybug;
}
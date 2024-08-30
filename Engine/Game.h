#pragma once

class Game abstract
{
public:
    static Game * Initialize();

public:
    virtual ~Game() = default;

public:
    virtual void  Start() abstract;
    virtual bool Update() abstract;
    virtual void    End() abstract;
};
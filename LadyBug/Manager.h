#pragma once

#include <vector>

#include "Framework/Time.h"

#include "Actor.h"

class Manager abstract
{
public:
    virtual ~Manager() = default;

    virtual void Update()
    {
        Elapsed += Time::GetDelta();

        if (Interval <= Elapsed)
        {
            Spawn();

            Elapsed = fmodf(Elapsed, Interval);
        }

        for (Actor * const actor : Actors)
        {
            if (actor->GetValid() == true)
            {
                actor->Update();
                actor->Render();
            }
        }
    }

protected:
    virtual void Spawn() abstract;

protected:
    std::vector<Actor *> Actors;

    float Elapsed  = { 0.0f };
    float Interval = { 0.0f };
};
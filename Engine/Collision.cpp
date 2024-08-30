#include <Windows.h>

#include <list>
#include <map>

#include "Collision.h"

namespace Collision
{
    namespace
    {
        std::map<Collision::Group, std::list<Component const *>> Circles;

        bool Collide(Component const & X, Component const & Y)
        {
            return Length(X.Location - Y.Location) <= X.Radius + Y.Radius;
        }
    }

    Component::Component(Collision::Group const group) : Group(group)
    {
        Circles[Group].push_back(this);
    }

    Component::~Component()
    {
        Circles[Group].erase(std::find(Circles[Group].cbegin(), Circles[Group].cend(), this));
    }

    void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
    {
        switch (uMessage)
        {
            case WM_APP:
            {
                for (auto i = Circles.cbegin(); i != Circles.cend(); ++i)
                {
                    auto j = i;

                    while (++j != Circles.cend())
                    {
                        for (auto k : i->second)
                        {
                            if ((*k).Activated == false)
                                continue;

                            for (auto l : j->second)
                            {
                                if ((*l).Activated == false)
                                    continue;

                                if (Collide(*k, *l) == true)
                                {
                                    if (k->Event != nullptr)
                                        k->Event(j->first);

                                    if (l->Event != nullptr)
                                        l->Event(i->first);
                                }
                            }
                        }
                    }
                }
                
                return;
            }
        }
    }
}
#include <Windows.h>

#include "Game.h"

namespace Collision { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }
namespace Input     { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }
namespace Rendering { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }
namespace Time      { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }

namespace Framework
{
    namespace { Game * const Portfolio = Game::Initialize(); }

    LRESULT CALLBACK Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
    {
        switch(uMessage)
        {
            case WM_CREATE:
            {
                Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);

                Portfolio->Start();

                return 0;
            }
            case WM_APP:
            {
                if(Portfolio->Update() == true)
                {
                    Collision::Procedure(hWindow, uMessage, wParameter, lParameter);
                        Input::Procedure(hWindow, uMessage, wParameter, lParameter);
                    Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);
                         Time::Procedure(hWindow, uMessage, wParameter, lParameter);
                }
                else
                {
                    DestroyWindow(hWindow);
                }

                return 0;
            }
            case WM_DESTROY:
            {
                Portfolio->End();

                delete Portfolio;

                Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);

                PostQuitMessage(0);

                return 0;
            }
            case WM_MOUSEMOVE:
            {
                Input::Procedure(hWindow, uMessage, wParameter, lParameter);

                return 0;
            }
            case WM_SIZE:
            {
                Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);

                return 0;
            }
            default:
            {
                return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
            }
        }
    }
}
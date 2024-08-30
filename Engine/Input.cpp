#include <Windows.h>

#include "Input.h"

namespace Input
{
    namespace
    {
        POINTS Cursor;
    }

    short GetCursorX() { return Cursor.x; }
    short GetCursorY() { return Cursor.y; }

    void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
    {
        switch(uMessage)
        {
            case WM_MOUSEMOVE:
            {
                Cursor.x = LOWORD(lParameter);
                Cursor.y = HIWORD(lParameter);

                return;
            }
        }
    }
}
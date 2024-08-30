#include <Windows.h>

namespace Framework
{
    LRESULT CALLBACK Procedure(HWND const, UINT const, WPARAM const, LPARAM const);
}

int APIENTRY WinMain
(
    _In_     HINSTANCE const hInstance,
    _In_opt_ HINSTANCE const hPrevInstance,
    _In_     LPSTR     const lpCmdLine,
    _In_     int       const nShowCmd
)
{
    HWND hWindow = HWND();
    {
        WNDCLASSEX Class = WNDCLASSEX();

        Class.cbSize        = sizeof(WNDCLASSEX);
        Class.lpfnWndProc   = Framework::Procedure;
        Class.hInstance     = hInstance;
        Class.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
        Class.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        Class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        Class.lpszClassName = "Window";
        Class.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);

        RegisterClassEx(&Class);
    }
    {
        CREATESTRUCT Window = CREATESTRUCT();

        Window.lpszClass = "Window";
        Window.lpszName  = "Ladybug";
        Window.style     = WS_CAPTION | WS_SYSMENU;
        Window.cx        = 600;
        Window.cy        = 900;
        Window.hInstance = hInstance;

        {
            SetProcessDPIAware();

            RECT Rect = RECT();

            Rect.left   = 0;
            Rect.top    = 0;
            Rect.right  = Window.cx;
            Rect.bottom = Window.cy;

            AdjustWindowRectEx(&Rect, Window.style, static_cast<bool>(Window.hMenu), Window.dwExStyle);

            Window.cx = Rect.right  - Rect.left;
            Window.cy = Rect.bottom - Rect.top;

            Window.x = (GetSystemMetrics(SM_CXSCREEN) - Window.cx) / 2;
            Window.y = (GetSystemMetrics(SM_CYSCREEN) - Window.cy) / 2;
        }

        hWindow = CreateWindowEx
        (
            Window.dwExStyle,
            Window.lpszClass,
            Window.lpszName,
            Window.style,
            Window.x,
            Window.y,
            Window.cx,
            Window.cy,
            Window.hwndParent,
            Window.hMenu,
            Window.hInstance,
            Window.lpCreateParams
        );

        ShowWindow(hWindow, SW_RESTORE);
    }
    {
        MSG Message = MSG();

        while(true)
        {
            if(PeekMessage(&Message, HWND(), WM_NULL, WM_NULL, PM_REMOVE))
            {
                if(Message.message == WM_QUIT)
                    return static_cast<int>(Message.wParam);

                DispatchMessage(&Message);
            }
            else
            {
                SendMessage(hWindow, WM_APP, 0, 0);
            }
        }
    }
}
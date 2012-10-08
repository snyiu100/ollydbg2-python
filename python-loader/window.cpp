#include "window.hpp"
#include "plugin.h"

LRESULT CALLBACK CommandLineWinProc(
  _In_  HWND hwnd,
  _In_  UINT uMsg,
  _In_  WPARAM wParam,
  _In_  LPARAM lParam
)
{
    PRECT rect = NULL;
    DWORD width = 0;

    switch (uMsg) 
    { 
        case WM_CREATE: 
            // Initialize the window. 
            return 0; 
 
        case WM_PAINT: 
            // Paint the window's client area. 
            return 0; 
 
        case WM_SIZING: 
            // Update the position of the window even if the parent window is resized
            rect = (PRECT)lParam;
            width = (rect->right - rect->left) - 10;
            Addtolist(0, RED, L"lolilol\n");

            MoveWindow(
                hwnd,
                0,
                rect->bottom,
                width,
                25,
                TRUE
            );
            
            return 0;  

        case WM_DESTROY: 
            // Clean up window-specific data objects. 
            PostQuitMessage(0);
            return 0; 
 
        // 
        // Process other messages. 
        // 
 
        default: 
            return DefWindowProc(hwnd, uMsg, wParam, lParam); 
    }

    return 0;
}

BOOL CreateCommandLineWindow(HWND hParent, HINSTANCE hInst)
{
    HWND hCmdLine;
    RECT rect = {0};
    DWORD width = 0;

    GetWindowRect(hParent, &rect);

    // We want an editbox as large the window is, minus the scrollbar
    width = (rect.right - rect.left) - 10;

    hCmdLine = CreateWindowEx(
        WS_EX_LTRREADING,
        L"EDIT",
        NULL,
        WS_CHILD,
        0,
        rect.bottom / 2,
        width,
        100,
        hParent,
        NULL,
        hInst,
        NULL
    );

    if(hCmdLine == NULL)
        return FALSE;

    SetWindowLong(hCmdLine, GWL_HWNDPARENT, (LONG)hParent);

    ShowWindow(hCmdLine, SW_SHOW);

    return TRUE;
}
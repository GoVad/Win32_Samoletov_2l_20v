#ifndef UNICODE
#define UNICODE
#endif 

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

LPARAM CALLBACK WindowProc1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND mhwnd;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc1;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    mhwnd = CreateWindow(
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        0, 0,
        800, 200,

        NULL,       // Parent window    
        0,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    CreateWindow(CLASS_NAME, L"1", WS_OVERLAPPEDWINDOW|WS_CHILD|WS_VISIBLE,
        10, 10, 150, 100, mhwnd, 0, 0, 0);
    CreateWindow(CLASS_NAME, L"2", WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE,
        200, 10, 150, 100, mhwnd, 0, 0, 0);
    CreateWindow(CLASS_NAME, L"3", WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE,
        400, 10, 150, 100, mhwnd, 0, 0, 0);
    CreateWindow(CLASS_NAME, L"4", WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE,
        600, 10, 150, 100, mhwnd, 0, 0, 0);

    ShowWindow(mhwnd, nCmdShow);
    SetFocus(mhwnd);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LPARAM CALLBACK WindowProc1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, HBRUSH(RGB(255, 255, 255)));
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        if (hwnd == mhwnd) break;
        auto wstr = new wchar_t[SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0)];
        GetWindowText(hwnd, wstr, SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0) + 1);
        MessageBox(0, wstr, wstr, MB_OK);
        break;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
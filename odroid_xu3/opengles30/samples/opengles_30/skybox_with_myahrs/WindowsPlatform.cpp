/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include "WindowsPlatform.h"

#include <windowsx.h>

namespace MaliSDK
{
    Platform* WindowsPlatform::instance = NULL;

    WindowsPlatform::WindowsPlatform(void)
    {
    }

    Platform* WindowsPlatform::getInstance(void)
    {
        if (instance == NULL)
        {
            instance = new WindowsPlatform();
        }
        return instance;
    }

    void WindowsPlatform::createWindow(int width, int height)
    {
        WNDCLASS windowClass;
        RECT rectangle;
        HINSTANCE hInstance;

        rectangle.left = 0L;
        rectangle.right = (long)width;
        rectangle.top = 0L;
        rectangle.bottom = (long)height;

        hInstance = GetModuleHandle(NULL);

        windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        windowClass.lpfnWndProc = (WNDPROC)WindowsPlatform::processWindow;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = hInstance;
        windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        windowClass.hbrBackground = NULL;
        windowClass.lpszMenuName = NULL;
        windowClass.lpszClassName = "OGLES";

        RegisterClass(&windowClass);

        AdjustWindowRectEx(&rectangle, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

        window = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, "OGLES", "Mali OpenGL ES SDK", WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 200, 200, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, NULL, NULL, hInstance, NULL);

        ShowWindow(window, SW_SHOW);
        SetForegroundWindow(window);
        SetFocus(window);

        deviceContext = GetDC(window);
    }

    void WindowsPlatform::destroyWindow(void)
    {
        ReleaseDC(window, deviceContext);
        DestroyWindow(window);
    }

    LRESULT CALLBACK WindowsPlatform::processWindow(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
    {
        switch(uiMsg) {
            case WM_CLOSE:
                PostQuitMessage(0);
                break;

            case WM_ACTIVATE:
            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_SIZE:
                break;

            default:
                return DefWindowProc(hWnd, uiMsg, wParam, lParam);
                break;
        }

        return 0;
    }

    Platform::WindowStatus WindowsPlatform::checkWindow()
    {
        if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE) == 0)
        {
            /* No messages to process. */
            Platform::WINDOW_IDLE;
        }

        switch(message.message)
        {
            case WM_QUIT:
                return Platform::WINDOW_EXIT;
                break;
            case WM_LBUTTONDOWN:
                TranslateMessage(&message);
                DispatchMessage(&message);
                return Platform::WINDOW_CLICK;
                break;
            default:
                TranslateMessage(&message);
                DispatchMessage(&message);
                break;
        }

        return Platform::WINDOW_IDLE;
    }
}

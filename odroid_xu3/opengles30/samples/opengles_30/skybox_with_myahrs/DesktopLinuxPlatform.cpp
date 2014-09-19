/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include "DesktopLinuxPlatform.h"

namespace MaliSDK
{
    Platform* DesktopLinuxPlatform::instance = NULL;

    DesktopLinuxPlatform::DesktopLinuxPlatform(void)
    {

    }

    Platform* DesktopLinuxPlatform::getInstance(void)
    {
        if (instance == NULL)
        {
            instance = new DesktopLinuxPlatform();
        }
        return instance;
    }

    /**
     * A window is not actually created by this function.
     * Call createX11Window after the EGL display has been initialized to get a window.
     */
    void DesktopLinuxPlatform::createWindow(int width, int height)
    {
        windowWidth = width;
        windowHeight = height;
    }

    bool DesktopLinuxPlatform::createX11Window(void)
    {
        XSetWindowAttributes windowAttributes;
        XSizeHints sizeHints;
        XEvent event;
        XVisualInfo visualInfoTemplate;

        unsigned long mask;
        long screen;

        int visualID, numberOfVisuals;

        display = XOpenDisplay(NULL);

        screen = DefaultScreen(display);

        eglGetConfigAttrib(EGLRuntime::display, EGLRuntime::config, EGL_NATIVE_VISUAL_ID, &visualID);
        visualInfoTemplate.visualid = visualID;
        visual = XGetVisualInfo(display, VisualIDMask, &visualInfoTemplate, &numberOfVisuals);

        if (visual == NULL)
        {
            LOGE("Couldn't get X visual info\n");
            return false;
        }

        colormap = XCreateColormap(display, RootWindow(display, screen), visual->visual, AllocNone);

        windowAttributes.colormap = colormap;
        windowAttributes.background_pixel = 0xFFFFFFFF;
        windowAttributes.border_pixel = 0;
        windowAttributes.event_mask = StructureNotifyMask | ExposureMask;

        mask = CWBackPixel | CWBorderPixel | CWEventMask | CWColormap;

        window = XCreateWindow(display, RootWindow(display, screen), 0, 0, windowWidth, windowHeight,
                               0, visual->depth, InputOutput, visual->visual, mask, &windowAttributes);
        sizeHints.flags = USPosition;
        sizeHints.x = 10;
        sizeHints.y = 10;

        XSetStandardProperties(display, window, "Mali OpenGL ES SDK", "", None, 0, 0, &sizeHints);
        XMapWindow(display, window);
        XIfEvent(display, &event, wait_for_map, (char*)&window);
        XSetWMColormapWindows(display, window, &window, 1);
        XFlush(display);

        /* Process Window Close Event through event handler, so XNextEvent does not fail. */
        Atom delWindow = XInternAtom(display, "WM_DELETE_WINDOW", 0);
        Status status = XSetWMProtocols(display, window, &delWindow, 1);
        
        switch (status)
        {
            case BadAlloc:
            {
                printf("The X server failed to allocate the requested resource or server memory.\n");
                exit(status);
            }
            
            case BadWindow:
            {
                printf("A value for a window argument does not name a defined Window.\n");
                exit(status);
            }
        }
        
        XSelectInput(display, window, ExposureMask | ButtonPressMask);

        return true;
    }

    void DesktopLinuxPlatform::destroyWindow(void)
    {
        XDestroyWindow(display, window);
        XFreeColormap(display, colormap);
        XFree(visual);
        XCloseDisplay(display);
    }

    Platform::WindowStatus DesktopLinuxPlatform::checkWindow(void)
    {
        XEvent event;

        while (XPending(display) > 0)
        {
            XNextEvent(display, &event);

            if (event.type == ButtonPress || event.type == ClientMessage)
            {
                return Platform::WINDOW_CLICK;
            }
        }
        return Platform::WINDOW_IDLE;
    }

    Bool DesktopLinuxPlatform::wait_for_map(Display *display, XEvent *event, char *windowPointer)
    {
        return (event->type == MapNotify && event->xmap.window == (*((Window*)windowPointer)));
    }
}

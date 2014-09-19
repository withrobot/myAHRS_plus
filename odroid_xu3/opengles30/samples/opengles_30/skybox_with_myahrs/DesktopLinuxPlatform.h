/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef DESKTOPLINUXPLATFORM_H
#define DESKTOPLINUXPLATFORM_H

#include <cstdlib>
#include <EGL/egl.h>

#include "Platform.h"

namespace MaliSDK
{
    /**
     * \brief Platform specific functions for a Desktop Linux platform.
     */
    class DesktopLinuxPlatform : public Platform
    {
    private:
        /**
         * \brief The width of the window (in pixels).
         */
        int windowWidth;

        /**
         * \brief The height of the window (in pixels).
         */
        int windowHeight;

        /**
         * \brief An X11 ColorMap.
         *
         * See X11 documentation for more details.
         */
        Colormap colormap;

        /**
         * \brief An X11 XVisualInfo.
         *
         * See X11 documentation for more details.
         */
        XVisualInfo *visual;

        /**
         * \brief The only instance of this class.
         */
        static Platform* instance;

        /**
         * \brief Default constructor.
         */
        DesktopLinuxPlatform(void);

        /**
         * \brief Callback for X11 events.
         *
         * Waits for map notification.
         */
        static Bool wait_for_map(Display *display, XEvent *event, char *windowPointer);
    public:
        /**
         * \brief Get the singleton instance of this class.
         *
         * If the instance does not exist, it is created.
         * \return The only instance of this class.
         */
        static Platform* getInstance(void);

        virtual void createWindow(int width, int height);
        virtual void destroyWindow(void);
        virtual WindowStatus checkWindow(void);

        /**
         * \brief Create an X11 window.
         *
         * It is used by EGLRuntime::initializeEGL, and can be called
         * only after having initialized the EGL display.
         */
        bool createX11Window(void);
    };
}
#endif /* DESKTOPLINUXPLATFORM_H */
/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include <cstdlib>
#include <sys/fcntl.h>
#include <sys/unistd.h>

#include "LinuxOnARMPlatform.h"

namespace MaliSDK
{
    Platform* LinuxOnARMPlatform::instance = NULL;

    LinuxOnARMPlatform::LinuxOnARMPlatform(void)
    {

    }

    Platform* LinuxOnARMPlatform::getInstance(void)
    {
        if (instance == NULL)
        {
            instance = new LinuxOnARMPlatform();
        }
        return instance;
    }

    void LinuxOnARMPlatform::createWindow(int width, int height)
    {
        window = (fbdev_window *)calloc(1, sizeof(fbdev_window));
        if(window == NULL)
        {
            LOGE("Out of memory at %s:%i\n", __FILE__, __LINE__);
            exit(1);
        }
        window->width = width;
        window->height = height;
    }

    void LinuxOnARMPlatform::destroyWindow(void)
    {
        free(window);
    }

    Platform::WindowStatus LinuxOnARMPlatform::checkWindow(void)
    {
        return Platform::WINDOW_IDLE;
    }
}
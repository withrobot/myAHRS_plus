/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef LINUXONARMPLATFORM_H
#define LINUXONARMPLATFORM_H

#include <cstdlib>

#include "Platform.h"

namespace MaliSDK
{
    /**
     * \brief Platform specific functions for a Desktop Linux platform.
     */
    class LinuxOnARMPlatform : public Platform
    {
    private:
        /**
         * \brief The only instance of this class.
         */
        static Platform* instance;

        /**
         * \brief Default constructor.
         */
        LinuxOnARMPlatform(void);
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
    };
}
#endif /* LINUXONARMPLATFORM_H */


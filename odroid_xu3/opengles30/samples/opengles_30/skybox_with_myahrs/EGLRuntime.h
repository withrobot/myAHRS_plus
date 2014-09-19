/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef EGLRUNTIME_H
#define EGLRUNTIME_H

#include <EGL/egl.h>
#include <EGL/eglext.h>
#define EGL_CHECK(x) \
    x; \
    { \
        EGLint eglError = eglGetError(); \
        if(eglError != EGL_SUCCESS) { \
            LOGE("eglGetError() = %i (0x%.8x) at %s:%i\n", (signed int)eglError, (unsigned int)eglError, __FILE__, __LINE__); \
            exit(1); \
        } \
    }

namespace MaliSDK
{
    /**
     * \brief Functions for managing EGL
     *
     * EGL is the standard windowing environment on embeded devices and is required to use OpenGL ES.
     */
    class EGLRuntime
    {
    private:
        /**
         * \brief Search for an EGL config with the attributes set in configAttributes.
         * \param[in] strictMatch If true, will attempt to match exactly the attributes set in configAttributes.
         * Otherwise, the first config found which meets 'at least' the required attributes (as determined by the EGL specification)
         * will be returned.
         * \return An EGL config with the required attributes.
         */
        static EGLConfig findConfig(bool strictMatch);

        /**
         * \brief Used to specify the EGL attributes we require from a configuration.
         *
         * Passed to eglChooseConfig() in order to find a matching configuration.
         */
        static EGLint configAttributes [];

        /**
         * \brief Used to specify the EGL attributes we require from a context.
         *
         * Passed to eglCreateContext() in order to get the correct context type.
         */
        static EGLint contextAttributes [];

        /**
         * \brief Used to specify the EGL attributes we require from a window surface.
         *
         * Passed to eglCreateWindowSurface() to get the required window surface type.
         */
        static EGLint windowAttributes [];


    public:
        /**
         * \brief Set the value of EGL_SAMPLES (AntiAliasing level) to be requested.
         *
         * Used when initializeEGL() is called to select a config with requiredEGLSamples level of AntiAliasing.
         *
         * \param[in] requiredEGLSamples The Level of AntiAliasing required.
         * \note It is not guaranteed that a config with the required level of AnitAliasing will be found.
         * If it is not possible to find a matching config with the requested level, EGL_SAMPLES will be set to zero
         * and the search for a config will start again.
         */
        static void setEGLSamples(EGLint requiredEGLSamples);

        /**
         * \brief An enum to define OpenGL ES versions.
         */
        enum OpenGLESVersion {OPENGLES1, OPENGLES2, OPENGLES3};

        /**
         * \brief The EGL display in use (a platform native window handle).
         *
         * Initialized by initializeEGL().
         */
        static EGLDisplay display;

        /**
         * \brief The EGL context in use.
         *
         * Created by initializeEGL() using the selected config and the API
         * version requested (OpenGL ES 1.x or OpenGL ES 2.0).
         */
        static EGLContext context;

        /**
         * \brief The selected EGL config which matches the required attributes.
         */
        static EGLConfig config;

        /**
         * \brief The EGL surface in use.
         *
         * Initialized by initializeEGL(). This surface is of window type and is used for
         * rendering to the native window.
         */
        static EGLSurface surface;

        /**
         * \brief Setup EGL environment.
         *
         * Finds a suitable window configuration and sets up the required context.
         * Different configurations are requested depending on the platform.
         * \param[in] requestedAPIVersion The API version required (OpenGL ES 1.x or OpenGLES 2.0).
         */
        static void initializeEGL(OpenGLESVersion requestedAPIVersion);

        /**
         * \brief Shuts down EGL.
         */
        static void terminateEGL(void);
    };
}

#endif /* EGLRUNTIME_H */
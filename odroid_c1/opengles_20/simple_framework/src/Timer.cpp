/*
 * This proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include "Timer.h"

#if defined(_WIN32)

#include <cstdio>
#include <windows.h>

namespace MaliSDK
{
    Timer::Timer()
    {
        LARGE_INTEGER l;
        QueryPerformanceFrequency(&l);
        invFreq = 1.0f / l.QuadPart;
        lastInterval = 0.0f;
        frameCount = 0;
        lastFpsUpdate = 0.0f;
        reset();
        fps = 0.0f;
        lastTime = 0.0f;
    }

    void Timer::reset()
    {
        LARGE_INTEGER l;
        QueryPerformanceCounter(&l);
        resetStamp = (((double)l.QuadPart) * invFreq);
    }

    float Timer::getTime()
    {
        LARGE_INTEGER l;
        QueryPerformanceCounter(&l);
        return (float)(((double)l.QuadPart) * invFreq - resetStamp);
    }

    float Timer::getInterval()
    {
        float time = getTime();
        float interval = time - lastInterval;
        lastInterval = time;
        return interval;
    }

    float Timer::getFPS()
    {
        float time = getTime();
        frameCount++;
        if (time-lastFpsUpdate > 1.0f)
        {
            fps = (float)frameCount / (time-lastFpsUpdate);
            lastFpsUpdate = time;
            frameCount = 0;
        }
        return fps;
    }
}
#else

#include <sys/time.h>

namespace MaliSDK
{
    Timer::Timer()
        : startTime()
        , currentTime()
        , lastIntervalTime(0.0f)
        , frameCount(0)
        , fpsTime(0.0f)
        , fps(0.0f)
    {    
        startTime.tv_sec = 0;
        startTime.tv_usec = 0;
        currentTime.tv_sec = 0;
        currentTime.tv_usec = 0;

        reset();
    }

    void Timer::reset()
    {
        gettimeofday(&startTime, NULL);
        lastIntervalTime = 0.0;

        frameCount = 0;
        fpsTime = 0.0f;
    }

    float Timer::getTime()
    {
        gettimeofday(&currentTime, NULL);
        float seconds = (currentTime.tv_sec - startTime.tv_sec);
        float milliseconds = (float(currentTime.tv_usec - startTime.tv_usec)) / 1000000.0f;
        return seconds + milliseconds;
    }

    float Timer::getInterval()
    {
        float time = getTime();
        float interval = time - lastIntervalTime;
        lastIntervalTime = time;
        return interval;
    }

    float Timer::getFPS()
    {
        if (getTime() - fpsTime > 1.0f)
        {
            fps = static_cast<float>(frameCount) / (getTime() - fpsTime);
            frameCount = 0;
            fpsTime = getTime();
        }
        ++frameCount;
        return fps;
    }
}
#endif

namespace MaliSDK
{
    bool Timer::isTimePassed(float seconds)
    {
        float time = getTime();
        if (time - lastTime > seconds)
        {
            lastTime = time;
            return true;
        }
        return false;
    }
}
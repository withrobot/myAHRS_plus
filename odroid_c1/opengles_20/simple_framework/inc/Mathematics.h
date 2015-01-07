/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include "VectorTypes.h"

#include <cmath>
#include <cstdlib>
/**
 * \file Mathematics.h
 * \brief Mathematic functions
 */

#ifndef M_PI
/**
 * \brief The value of pi.
 */
#define M_PI 3.14159265358979323846f
#endif /* M_PI */

namespace MaliSDK
{
    /**
     * \brief Compute Euclidean 2-dimensional distance between two points on XY plane.
     * \param[in] point1 First point.
     * \param[in] point2 Second point.
     * \return Distance between points on XY plane.
     */
    inline float distanceBetweenPoints(const Vec2f& point1, const Vec2f& point2)
    {
	    return sqrtf((point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y));
    }

    /**
     * \brief Get the sign of a number.
     * \param[in] f Value to check the sign of.
     * \return -1.0 if the number's sign is minus, 1.0 if the number's sign is plus and 0.0 if the number's sign is indefinite.
     */
    inline float signum(float f)
    {
	    if (f > 0.0f) 
	    {
		    return  1.0f;
	    }
        
	    if (f < 0.0f) 
	    {
		    return -1.0f;
	    }

	    return 0.0f;
    }

    /**
     * \brief Generate random number in the 0.0 to 1.0 range. 
     * \return Random number in the range 0.0 to 1.0.
     */
    inline float uniformRandomNumber()
    {
	    return rand() / float(RAND_MAX);
    }

    /**
     * \brief Convert an angle in degrees to radians.
     * \param[in] degrees The angle (in degrees) to convert to radians.
     */
    inline float degreesToRadians(float degrees)
    {
        return M_PI * degrees / 180.0f;
    }
}
#endif /* MATHEMATICS_H */
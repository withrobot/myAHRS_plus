/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014 ARM Limited
 *     ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "Quaternions.h"

/* Please see the header for specification */
Quaternion construct_quaternion(float x, float y, float z, float degs)
{
    Quaternion init = { 0.0f, 0.0f, 0.0f, 0.0f };

    float ang = (float) M_PI * degs / 180.0f;
    float res = sin(ang / 2.0f);

    init.w = cos(ang / 2.0f);
    init.x = x * res;
    init.y = y * res;
    init.z = z * res;

    return init;
}

/* Please see the header for specification */
void construct_modelview_matrix(Quaternion quaternion, float* mat)
{
    if (mat == 0)
    {
        fprintf(stderr, "Pointer to a modelview matrix points to NULL.\n");

        exit(EXIT_FAILURE);
    }

    mat[ 0] = 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z);
    mat[ 1] = 2.0f        * (quaternion.x * quaternion.y + quaternion.z * quaternion.w);
    mat[ 2] = 2.0f        * (quaternion.x * quaternion.z - quaternion.y * quaternion.w);
    mat[ 3] = 0.0f;
    mat[ 4] = 2.0f        * (quaternion.x * quaternion.y - quaternion.z * quaternion.w);
    mat[ 5] = 1.0f - 2.0f * (quaternion.x * quaternion.x + quaternion.z * quaternion.z);
    mat[ 6] = 2.0f        * (quaternion.z * quaternion.y + quaternion.x * quaternion.w);
    mat[ 7] = 0.0f;
    mat[ 8] = 2.0f        * ( quaternion.x * quaternion.z + quaternion.y * quaternion.w);
    mat[ 9] = 2.0f        * ( quaternion.y * quaternion.z - quaternion.x * quaternion.w);
    mat[10] = 1.0f - 2.0f * ( quaternion.x * quaternion.x + quaternion.y * quaternion.y);
    mat[11] = 0.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

/* Please see the header for specification */
Quaternion multiply_quaternions(Quaternion a, Quaternion b)
{
    Quaternion res;

    res.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    res.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    res.y = a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z;
    res.z = a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x;

    return res;
}
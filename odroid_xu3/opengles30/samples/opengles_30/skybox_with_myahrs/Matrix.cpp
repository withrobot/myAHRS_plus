/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014 ARM Limited
 *     ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include "Matrix.h"
#include "Platform.h"

#include <cmath>
#include <cstring>
#include <cstdlib>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif /* M_PI */

namespace MaliSDK
{
    /* Identity matrix. */
    const float Matrix::identityArray[16] =
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    /* Please see header for specification. */
    Matrix::Matrix(const float* array)
    {
        memcpy(elements, array, 16 * sizeof(float));
    }

    /* Please see header for specification. */
    Matrix Matrix::identityMatrix = Matrix(identityArray);

    /* Please see header for specification. */
    Matrix::Matrix(void){}

    /* Please see header for specification. */
    float* Matrix::getAsArray(void)
    {
        return elements;
    }

    /* Please see header for specification. */
    Matrix& Matrix::operator=(const Matrix &another)
    {
        if(this != &another)
        {
            memcpy(this->elements, another.elements, 16 * sizeof(float));
        }

        return *this;
    }

    /* Please see header for specification. */
    Matrix Matrix::matrixOrthographic(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        Matrix result = identityMatrix;

        result.elements[0]  = 2.0f / (right - left);
        result.elements[12] = -(right + left) / (right - left);

        result.elements[5]  = 2.0f / (top - bottom);
        result.elements[13] = -(top + bottom) / (top - bottom);

        result.elements[10] = -2.0f / (zFar - zNear);
        result.elements[14] = -(zFar + zNear) / (zFar - zNear);

        return result;
    }
}
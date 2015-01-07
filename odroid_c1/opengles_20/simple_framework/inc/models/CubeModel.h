/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef CUBE_MODEL_H
#define CUBE_MODEL_H

#include "VectorTypes.h"

namespace MaliSDK
{
    /**
     * \brief Functions for generating cube shapes.
     */
    class CubeModel
    {
    public:
        /** 
         * \brief Compute coordinates of points which make up a cube.
         *
         * \param[in] scalingFactor Scaling factor indicating size of a cube.
         * \param[out] numberOfCoordinates  Number of generated coordinates.
         * \param[out] coordinates Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getTriangleRepresentation(float scalingFactor, int* numberOfCoordinates, float** coordinates);

        /** 
         * \brief Create normals for a cube which was created with getTriangleRepresentation() function.
         *
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] normals Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getNormals(int* numberOfCoordinates, float** normals);
    };
}
#endif /* CUBE_MODEL_H */
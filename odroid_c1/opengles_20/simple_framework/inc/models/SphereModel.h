/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef SPHERE_MODEL_H
#define SPHERE_MODEL_H

#include "VectorTypes.h"

namespace MaliSDK
{
    /**
     * \brief Functions for generating sphere shapes.
     */
    class SphereModel
    {
    private:
        /**
         * \brief Compute coordinates of points which make up a sphere. 
         *
         * \param[in] radius Radius of a sphere. Has to be greater than zero.
         * \param[in] numberOfSamples Sphere consists of numberOfSamples circles and numberOfSamples points lying on one circle. Has to be greater than zero.
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] coordinates Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getPointRepresentation(const float radius, const int numberOfSamples, int* numberOfCoordinates, float** coordinates);
    public:
        /** 
         * \brief Create triangular representation of a sphere. 
         *
         * For each point of each circle (excluding last circle) there are two triangles created according to rule described in example below:
         *
         *                A2___________.B2
         *                . \       .  / |
         *                |. \   .    /  |
         *                | . A1____B1   |
         *                |  . |     |.  |
         *                |   D1____C1 . |
         *                |  /    .   \ .|
         *                | /  .       \ .
         *               D2 .___________C2
         *
         * Points named A1, B1, C1 and D1 create a first circle of sphere and points named A2, B2, C2 and D2 create the second one 
         * (if numberOfSamples is equal to 4). For each loop iteration, for each point lying at one circle of sphere there are 2 triangles created:
         * for point A1:  A1 B1 B2,   A1 B2 A2
         * for point B1:  B1 C1 C2,   B1 C2 B2
         * for point C1:  C1 D1 D2,   C1 D2 C2
         * for point D1:  D1 A1 A2,   D1 A2 D2
         *
         * \param[in] radius Radius of a sphere. Has to be greater than zero.
         * \param[in] numberOfSamples A sphere consists of numberOfSamples circles and numberOfSamples points lying on one circle. Has to be greater than zero.
         * \param[out] numberOfCoordinates Number of generated coordinates. 
         * \param[out] coordinates Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getTriangleRepresentation(const float radius, const int numberOfSamples, int* numberOfCoordinates, float** coordinates);
    };
}
#endif /* SPHERE_MODEL_H */
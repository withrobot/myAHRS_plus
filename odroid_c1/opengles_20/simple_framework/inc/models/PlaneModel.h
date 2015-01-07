/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef PLANE_MODEL_H
#define PLANE_MODEL_H

#include "VectorTypes.h"
#include "Matrix.h"

namespace MaliSDK
{
    /**
     * \brief Functions for generating Plane shapes.
     */
    class PlaneModel
    {
    public:
        /** 
         * \brief Get coordinates of points which make up a plane. The plane is located in XZ space.
         * 
         * Triangles are made up of 4 components per vertex.
         *
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] coordinates Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getTriangleRepresentation(int* numberOfCoordinates, float** coordinates);

        /**
         * \brief Get U/V 2D texture coordinates that can be mapped onto a plane generated from this class.
         *
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] uvCoordinates Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getTriangleRepresentationUVCoordinates(int* numberOfCoordinates, float** uvCoordinates);

        /** 
         * \brief Get normals for plane placed in XZ space.
         *
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] normals Deref will be used to store generated normals. Cannot be null.
         */
        static void getNormals(int* numberOfCoordinates, float** normals);

        /**
         * \brief Transform a plane by a matrix.
         *
         * \param[in] transform The transformation Matrix to apply to the plane.
         * \param[in] numberOfCoordinates Number of coordinates which make up the plane.
         * \param[in, out] coordinates Pointer to the verticies to be transformed. The transformed verticies will be returned in the same memory. Cannot be null.
         */
        static void transform(Matrix transform, int numberOfCoordinates, float** coordinates);
    };
}
#endif /* PLANE_MODEL_H */
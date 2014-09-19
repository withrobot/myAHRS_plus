/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include "PlaneModel.h"

#include "Mathematics.h"
#include "Platform.h"

#include <cassert>

namespace MaliSDK
{
    void PlaneModel::getTriangleRepresentationUVCoordinates(int* numberOfCoordinates, float** uvCoordinates)
    {
        /* Example:
         *  v   D __________ C
         *  .    |        / |
         * / \   |     /    |
         *  |    |  /       |
         *  |    |/_________|
         *  |   A            B
         *  |----------> u
         */

        if (uvCoordinates == NULL)
        {
            LOGE("Cannot use null pointer while calculating coordinates.");

            return;
        }

        /* 2 triangles, 3 points of triangle, 2 coordinates for each point. */
        const int numberOfUVCoordinates = 2 * 3 * 2;

        /* Allocate memory for result array. */
        *uvCoordinates = (float*) malloc (numberOfUVCoordinates * sizeof(float));

        /* Is allocation successfu?. */
        if (*uvCoordinates == NULL)
        {
            LOGE("Could not allocate memory for result array.");
            return;
        }
        
        /* Index of an array we will put new point coordinates at. */
        int currentIndex = 0;

        /*** First triangle. ***/
        /* A */
        /* u */ 
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++;
        /* v */ 
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++;
        /* B */
        /* u */ 
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* v */ 
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++;
        /* C */
        /* u */ 
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* v */ 
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++;

        /*** Second triangle. ***/
        /* A */
        /* u */
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++; 
        /* v */
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++; 
        /* C */
        /* u */
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++; 
        /* v */
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++; 
        /* D */
        /* u */
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++; 
        /* v */
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++; 

        if (numberOfCoordinates != NULL)
        {
            *numberOfCoordinates = numberOfUVCoordinates;
        }
    }

    void PlaneModel::getTriangleRepresentation(int* numberOfCoordinates, float** coordinates)
    {
        /* Example:
         *  z   D __________ C
         *  .    |        / |
         * / \   |     /    |
         *  |    |  /       |
         *  |    |/_________|
         *  |   A            B
         *  |----------> x
         */

        if (coordinates == NULL)
        {
            LOGE("Cannot use null pointer while calculating coordinates.");

            return;
        }

        /* 2 triangles, 3 points of triangle, 4 coordinates for each point. */
        const int numberOfSquareCoordinates = 2 * 3 * 4;

        /* Allocate memory for result array. */
        *coordinates = (float*) malloc (numberOfSquareCoordinates * sizeof(float));

        /* Is allocation successfu?. */
        if (*coordinates == NULL)
        {
            LOGE("Could not allocate memory for result array.");
            return;
        }
        
        /* Index of an array we will put new point coordinates at. */
        int currentIndex = 0;

        /* First triangle. */
        /* A */
        /* x */ 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /* y */ 
        (*coordinates)[currentIndex] =  0.0f;
        currentIndex++;
        /* z */ 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /* w */ 
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* B */
        /* x */ 
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /* y */ 
        (*coordinates)[currentIndex] =  0.0f;
        currentIndex++;
        /* z */ 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /* w */ 
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* C */
        /* x */ 
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /* y */ 
        (*coordinates)[currentIndex] =  0.0f;
        currentIndex++;
        /* z */ 
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /* w */ 
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;

        /* Second triangle. */
        /* A */
        /* x */
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        /* y */
        (*coordinates)[currentIndex] =  0.0f;
        currentIndex++; 
        /* z */
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /* w */ 
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* C */
        /* x */
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++; 
        /* y */
        (*coordinates)[currentIndex] = 0.0f;
        currentIndex++; 
        /* z */
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* w */ 
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* D */
        /* x */
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        /* y */
        (*coordinates)[currentIndex] =  0.0f;
        currentIndex++; 
        /* z */
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /* w */ 
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;

        if (numberOfCoordinates != NULL)
        {
            *numberOfCoordinates = numberOfSquareCoordinates;
        }
    }

    void PlaneModel::getNormals(int* numberOfCoordinates, float** normals)
    {
        if (normals == NULL)
        {
            LOGE("Cannot use null pointer while calculating coordinates.");

            return;
        }

        /* 2 triangles, 3 points of triangle, 3 coordinates for each point. */
        const int numberOfNormalsCoordinates = 2 * 3 * 3;
        /* Index of an array we will put new point coordinates at. */
        int currentIndex = 0;

        /* Allocate memory for result array. */
        *normals = (float*) malloc (numberOfNormalsCoordinates * sizeof(float));

        /* Is allocation successfu?. */
        if (*normals == NULL)
        {
            LOGE("Could not allocate memory for result array.");

            return;
        }

        for (int i = 0; i < numberOfNormalsCoordinates; i+=3)
        {
            (*normals)[currentIndex] = 0.0f;
            currentIndex++;
            (*normals)[currentIndex] = 1.0f;
            currentIndex++;
            (*normals)[currentIndex] = 0.0f;
            currentIndex++;
        }

        if (numberOfCoordinates != NULL)
        {
            *numberOfCoordinates = numberOfNormalsCoordinates;
        }
    }

    void PlaneModel::transform(Matrix transform, int numberOfCoordinates, float** squareCoordinates)
    {
        /* Loop through all the coordinates and transform them using the rotation matrix. */
        for (int allCoordinates = 0; allCoordinates < numberOfCoordinates; allCoordinates +=4)
        {
            Vec4f currentVertex = {(*squareCoordinates)[allCoordinates], (*squareCoordinates)[allCoordinates + 1], (*squareCoordinates)[allCoordinates + 2], (*squareCoordinates)[allCoordinates + 3]};

            Vec4f rotatedVertex = Matrix::vertexTransform(&currentVertex, &transform);

            (*squareCoordinates)[allCoordinates] = rotatedVertex.x;
            (*squareCoordinates)[allCoordinates + 1] = rotatedVertex.y;
            (*squareCoordinates)[allCoordinates + 2] = rotatedVertex.z;
            (*squareCoordinates)[allCoordinates + 3] = rotatedVertex.w;
        }
    }
}
/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014 ARM Limited
 *     ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef QUATERNION_H
    #define QUATERNION_H

    #ifndef M_PI
        #define M_PI 3.14159265358979323846
    #endif /* M_PI */

    /** Structure describing a single quaternion instance. */
    typedef struct Quaternion
    {
        /** Real part. */
        float w;
        /** X imaginary part. */
        float x;
        /** Y imaginary part. */
        float y;
        /** Z imaginary part. */
        float z;
    } Quaternion;

    /** Function that returns a new quaternion. It inserts the angle in the real part and the vector
     *  in the vector part, yielding a quaternion that represents a rotation around the axis.
     *  
     *  @param x    X coordinate of a vector defining a rotation axis.
     *  @param y    Y coordinate of a vector defining a rotation axis.
     *  @param z    Z coordinate of a vector defining a rotation axis.
     *  @param degs Rotation in degrees.
     *  @return     Result quaternion.
     */
    Quaternion construct_quaternion(float x, float y, float z, float degs);

    /** Constructs a modelview matrix based on a given quaternion.
     *
     *  @param quaternion Quaternion describing rotation angle and vector to be used for matrix creation.
     *  @param mat        Array to store a modelview matrix. Cannot be NULL.
     */
    void construct_modelview_matrix(Quaternion quaternion, float* mat);

    /** Multiplies quaternion a by b and returns the product.
     *  NOTE: quaternion multiplication is not commutative.
     *
     *  @param a Quaternion a.
     *  @param b Quaternion b.
     *  @return  Product a*b.
     */
    Quaternion multiply_quaternions(Quaternion a, Quaternion b);

#endif /* QUATERNION_H */
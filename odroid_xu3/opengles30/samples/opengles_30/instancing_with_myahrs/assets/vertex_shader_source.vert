#version 300 es

/*
 * This proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/*
 * palm, finger 1~5
 */ 
const int numberOfCubes = 6;

const float pi = 3.14159265358979323846;

in      vec4 attributeColor;
in      vec4 attributePosition;
out     vec4 vertexColor;
uniform vec3 cameraVector;
uniform vec4 perspectiveVector;

/*
 *  2014.07.29 ('c')void 
 *    ref) http://en.wikibooks.org/wiki/GLSL_Programming/Vector_and_Matrix_Operations
 */
uniform float distance_from_center[numberOfCubes];
uniform vec3  rotation_of_cube[numberOfCubes];
uniform vec3  rotation_of_center;

/*
 * We use uniform block in order to reduce amount of memory transfers to minimum. 
 * The uniform block uses data taken directly from a buffer object. 
 */
uniform CubesUniformBlock
{
    float startPosition[numberOfCubes];
    vec4  cubeColor[numberOfCubes];
};

void main()
{
    mat4 tempMatrix;
    mat3 tempMatrix3;
    mat4 xRotationMatrix, yRotationMatrix, zRotationMatrix;

    float fieldOfView = 1.0 / tan(perspectiveVector.x * 0.5);

    float radius = distance_from_center[gl_InstanceID];
    vec3 location_offset = vec3(radius * cos(startPosition[gl_InstanceID]),
                                radius * sin(startPosition[gl_InstanceID]),
                                0.0);

    mat3 xRotationMatrix_tr = mat3 (1.0,  0.0,                                    0.0,                                
                                    0.0,  cos(pi * rotation_of_center.x / 180.0), sin(pi * rotation_of_center.x / 180.0), 
                                    0.0, -sin(pi * rotation_of_center.x / 180.0), cos(pi * rotation_of_center.x / 180.0));
                                
    mat3 yRotationMatrix_tr = mat3 (cos(pi * rotation_of_center.y / 180.0), 0.0, -sin(pi * rotation_of_center.y / 180.0), 
                                    0.0,                                    1.0,  0.0,                                 
                                    sin(pi * rotation_of_center.y / 180.0), 0.0,  cos(pi * rotation_of_center.y / 180.0));
                                
    mat3 zRotationMatrix_tr = mat3 ( cos(pi * rotation_of_center.z / 180.0), sin(pi * rotation_of_center.z / 180.0), 0.0,  
                                    -sin(pi * rotation_of_center.z / 180.0), cos(pi * rotation_of_center.z / 180.0), 0.0, 
                                     0.0,                                    0.0,                                    1.0);


    tempMatrix3 = xRotationMatrix_tr;
    tempMatrix3 = yRotationMatrix_tr * tempMatrix3;
    tempMatrix3 = zRotationMatrix_tr * tempMatrix3;

    vec3 locationOfCube = tempMatrix3 * location_offset;


    vec3 rotationOfube = rotation_of_cube[gl_InstanceID];
    
    /* 
     * Set different random colors for each cube. 
     * There is one color passed in per cube set for each cube (cubeColor[gl_InstanceID]).
     * There are also different colors per vertex of a cube (attributeColor).
     */
    vertexColor = attributeColor * cubeColor[gl_InstanceID];
    
    /* Create transformation matrices. */
    mat4 translationMatrix = mat4 (1.0,             0.0,             0.0,             0.0, 
                                   0.0,             1.0,             0.0,             0.0, 
                                   0.0,             0.0,             1.0,             0.0, 
                                   locationOfCube.x, locationOfCube.y, locationOfCube.z, 1.0);
                             

    /* camera */        
    const float cam_rotation_z_deg = 90.0; 

    zRotationMatrix = mat4 ( cos(pi * cam_rotation_z_deg / 180.0), sin(pi * cam_rotation_z_deg / 180.0), 0.0, 0.0, 
                            -sin(pi * cam_rotation_z_deg / 180.0), cos(pi * cam_rotation_z_deg / 180.0), 0.0, 0.0, 
                             0.0,                                  0.0,                                  1.0, 0.0, 
                             0.0,                                  0.0,                                  0.0, 1.0);

    mat4 cameraMatrix = mat4 (1.0,            0.0,            0.0,            0.0, 
                              0.0,            1.0,            0.0,            0.0, 
                              0.0,            0.0,            1.0,            0.0, 
                              cameraVector.x, cameraVector.y, cameraVector.z, 1.0);

    cameraMatrix = zRotationMatrix*cameraMatrix;                        


    /* cube */ 
    xRotationMatrix = mat4 (1.0,  0.0,                               0.0,                                0.0, 
                            0.0,  cos(pi * rotationOfube.x / 180.0), sin(pi * rotationOfube.x / 180.0),  0.0, 
                            0.0, -sin(pi * rotationOfube.x / 180.0), cos(pi * rotationOfube.x / 180.0),  0.0, 
                            0.0,  0.0,                               0.0,                                1.0);
                                
    yRotationMatrix = mat4 (cos(pi * rotationOfube.y / 180.0), 0.0, -sin(pi * rotationOfube.y / 180.0), 0.0, 
                            0.0,                               1.0, 0.0,                                0.0, 
                            sin(pi * rotationOfube.y / 180.0), 0.0, cos(pi * rotationOfube.y / 180.0),  0.0, 
                            0.0,                               0.0, 0.0,                                1.0);
                                
    zRotationMatrix = mat4 ( cos(pi * rotationOfube.z / 180.0), sin(pi * rotationOfube.z / 180.0), 0.0, 0.0, 
                            -sin(pi * rotationOfube.z / 180.0), cos(pi * rotationOfube.z / 180.0), 0.0, 0.0, 
                             0.0,                               0.0,                               1.0, 0.0, 
                             0.0,                               0.0,                               0.0, 1.0);
                                 
    mat4 perspectiveMatrix = mat4 (fieldOfView/perspectiveVector.y, 0.0,        0.0,                                                                                              0.0, 
                                   0.0,                            fieldOfView, 0.0,                                                                                              0.0, 
                                   0.0,                            0.0,        -(perspectiveVector.w + perspectiveVector.z) / (perspectiveVector.w - perspectiveVector.z),        -1.0, 
                                   0.0,                            0.0,        (-2.0 * perspectiveVector.w * perspectiveVector.z) / (perspectiveVector.w - perspectiveVector.z), 0.0);

    /* Compute rotation. */
    tempMatrix = xRotationMatrix;
    tempMatrix = yRotationMatrix * tempMatrix;
    tempMatrix = zRotationMatrix * tempMatrix;

    
    /* Compute translation. */
    tempMatrix = translationMatrix * tempMatrix;
    tempMatrix = cameraMatrix      * tempMatrix;
                
    /* Compute perspective. */
    tempMatrix = perspectiveMatrix * tempMatrix;
                
    /* Return gl_Position. */
    gl_Position = tempMatrix * attributePosition;
}
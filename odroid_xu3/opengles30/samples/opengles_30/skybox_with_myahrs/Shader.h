/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014 ARM Limited
 *     ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef SHADER_H
#define SHADER_H

#include <GLES3/gl3.h>

namespace MaliSDK
{
    /**
     * \brief Functions for working with OpenGL ES shaders.
     */
    class Shader
    {
        private:
            /**
             * \brief Load shader source from a file into memory.
             * \param[in] filename File name of the shader to load.
             * \return A character array containing the contents of the shader source file. 
             */
            static char* loadShader(const char* filename);

        public:
            /**
             * \brief Create shader, load in source, compile, and dump debug as necessary.
             *
             * Loads the OpenGL ES Shading Language code into memory.
             * Creates a shader using with the required shaderType using glCreateShader(shaderType) and then compiles it using glCompileShader.
             * The output from the compilation is checked for success and a log of the compilation errors is printed in the case of failure.
             * \param[out] shader The shader ID of the newly compiled shader.
             * \param[in] filename Filename of a file containing OpenGL ES SL source code.
             * \param[in] shaderType Passed to glCreateShader to define the type of shader being processed. Must be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
             */
            static void processShader(GLuint* shader, const char* filename, GLint shaderType);
    };
}
#endif /* SHADER_H */
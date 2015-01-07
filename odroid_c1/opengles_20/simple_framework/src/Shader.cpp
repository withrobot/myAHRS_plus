/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include "Shader.h"
#include "Platform.h"

#include <cstdio>
#include <cstdlib>

namespace MaliSDK
{
    void Shader::processShader(GLuint *shader, const char *filename, GLint shaderType)
    {  
        const char *strings[1] = { NULL };

        /* Create shader and load into GL. */
        *shader = GL_CHECK(glCreateShader(shaderType));
        strings[0] = loadShader(filename);
        GL_CHECK(glShaderSource(*shader, 1, strings, NULL));

        /* Clean up shader source. */
        free((void *)(strings[0]));
        strings[0] = NULL;

        /* Try compiling the shader. */
        GL_CHECK(glCompileShader(*shader));
        GLint status;
        GL_CHECK(glGetShaderiv(*shader, GL_COMPILE_STATUS, &status));

        /* Dump debug info (source and log) if compilation failed. */
        if(status != GL_TRUE) 
        {
            GLint length;
            char *debugSource = NULL;
            char *errorLog = NULL;

            /* Get shader source. */
            GL_CHECK(glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length));
            debugSource = (char *)malloc(length);
            GL_CHECK(glGetShaderSource(*shader, length, NULL, debugSource));
            LOGE("Debug source START:\n%s\nDebug source END\n\n", debugSource);
            free(debugSource);

            /* Now get the info log. */
            GL_CHECK(glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &length));
            errorLog = (char *)malloc(length);
            GL_CHECK(glGetShaderInfoLog(*shader, length, NULL, errorLog));
            LOGE("Log START:\n%s\nLog END\n\n", errorLog);
            free(errorLog);

            LOGE("Compilation FAILED!\n\n");
            exit(1);
        }
    }

    char* Shader::loadShader(const char *filename)
    {
        FILE *file = fopen(filename, "rb");
        if(file == NULL)
        {
            LOGE("Cannot read file '%s'\n", filename);
            exit(1);
        }
        /* Seek end of file. */
        fseek(file, 0, SEEK_END);
        /* Record the size of the file for memory allocation. */
        long length = ftell(file);
        /* Seek start of file again. */
        fseek(file, 0, SEEK_SET); 
        char *shader = (char *)calloc(length + 1, sizeof(char));
        if(shader == NULL)
        {
            LOGE("Out of memory at %s:%i\n", __FILE__, __LINE__);
            exit(1);
        }
        /* Read in the file */
        size_t numberOfBytesRead = fread(shader, sizeof(char), length, file);
        if (numberOfBytesRead != length) 
        {
            LOGE("Error reading %s (read %d of %d)", filename, numberOfBytesRead, length);
            exit(1);
        }
        shader[length] = '\0';
        fclose(file);

        return shader;
    }
}
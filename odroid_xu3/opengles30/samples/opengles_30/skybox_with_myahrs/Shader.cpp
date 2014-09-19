/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014 ARM Limited
 *     ALL RIGHTS RESERVED
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
    /* Please see header for specification. */
    void Shader::processShader(GLuint *shader, const char *filename, GLint shaderType)
    {
        const char *strings[1] = { NULL };

        /* Create shader and load into GL. */
        *shader    = GL_CHECK(glCreateShader(shaderType));
        strings[0] = loadShader(filename);

        GL_CHECK(glShaderSource(*shader, 1, strings, NULL));

        /* Clean up shader source. */
        FREE_CHECK(strings[0]);

        /* Try compiling the shader. */
        GL_CHECK(glCompileShader(*shader));

        GLint status = GL_FALSE;

        GL_CHECK(glGetShaderiv(*shader, GL_COMPILE_STATUS, &status));

        /* Dump debug info (source and log) if compilation failed. */
        if (status != GL_TRUE)
        {
            GLint length = 0;

            char *debugSource = NULL;
            char *errorLog    = NULL;

            MALLOC_CHECK(char*, debugSource, length);
            MALLOC_CHECK(char*, errorLog, length);

            /* Get shader source. */
            GL_CHECK(glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length));
            GL_CHECK(glGetShaderSource(*shader, length, NULL, debugSource));

            LOGD("<Shader source START>\n%s\n<Shader source END>\n\n", debugSource);
            FREE_CHECK(debugSource);

            /* Now get the info log. */
            GL_CHECK(glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &length));
            GL_CHECK(glGetShaderInfoLog(*shader, length, NULL, errorLog));

            LOGD("<Log START>\n%s\n<Log END>\n\n", errorLog);
            FREE_CHECK(errorLog);

            LOGE("Compilation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    /* Please see header for specification. */
    char* Shader::loadShader(const char *filename)
    {
        FILE *file = fopen(filename, "rb");

        if (file == NULL)
        {
            LOGF("Cannot read file [%s]\n", filename);
            exit(EXIT_FAILURE);
        }

        char *shader = NULL;

        /* Seek end of file. */
        fseek(file, 0, SEEK_END);

        /* Record the size of the file for memory allocation. */
        long length = ftell(file);

        /* Seek start of file again. */
        fseek(file, 0, SEEK_SET);

        MALLOC_CHECK(char*, shader, length + 1);

        /* Read in the file */
        size_t numberOfBytesRead = fread(shader, sizeof(char), length, file);

        if (numberOfBytesRead != length) 
        {
            LOGF("Error reading file [%s] (read %d of %ld).", filename, numberOfBytesRead, length);
            exit(EXIT_FAILURE);
        }

        shader[length] = '\0';
        fclose(file);

        return shader;
    }
}

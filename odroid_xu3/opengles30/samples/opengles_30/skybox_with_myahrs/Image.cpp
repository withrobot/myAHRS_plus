/*
 * This proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009 - 2013 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Image.h"

/* Disable deprecation warning on Windows. */
#ifdef _WIN32
    #pragma warning(push)
    #pragma warning(disable : 4996)
#endif /* _WIN32 */

/* Please see the header for specification. */
ImageFile load_ppm_file(const char* ppm_file_name)
{
    ImageFile image = { 0, 0, NULL };

    /* Constant numbers. */
    int max_color_value        = 255;
    int num_of_bytes_per_pixel = 3;
    int read_buffer_length     = 256;

    /* Constant strings. */
    const char comment_id    = '#';
    const char pixmap_mark[] = "P6\n";

    int   id_255          = 0; 
    int   height          = 0;
    char* line_str        = NULL;
    int   n_loaded_pixels = 0;
    char* pixels          = NULL;
    char* returned_str    = NULL;
    int   returned_value  = 0;
    int   width           = 0;

    FILE* pFile = fopen(ppm_file_name, "rb");
    
    if (pFile == NULL)
    {
        fprintf(stderr, "Error opening .ppm file.\n");

        goto return_now;
    }

    line_str = (char*) malloc(read_buffer_length);

    if (line_str == NULL)
    {
        fprintf(stderr, "Error allocating memory for string.\n");

        goto return_now;
    }

    /* Read the first line. */
    returned_str = fgets(line_str, read_buffer_length, pFile);

    if (returned_str == NULL)
    {
        fprintf(stderr, "Error reading .ppm file.\n");

        goto free_memory;
    }

    /* Verify whether the file begins with a "magic number" identifying the .ppm file type. */
    returned_value = strncmp(line_str, pixmap_mark, sizeof(pixmap_mark));

    if (returned_value != 0)
    {
        fprintf(stderr, "File does not contain P6 string in the header.\n");

        goto free_memory;
    }

    returned_str = fgets(line_str, read_buffer_length, pFile);

    /* Ignore any comments after P6 identifier, beginning with '#' */
    while (strncmp(line_str, &comment_id, sizeof(comment_id)) == 0)
    {
        returned_str = fgets(line_str, read_buffer_length, pFile);

        if (returned_str == NULL)
        {
            fprintf(stderr, "Error reading .ppm file.\n");

            goto free_memory;
        }
    }

    /* Read the pixmap dimensions. */
    returned_value = sscanf(line_str, "%d %d", &width, &height);

    /* Make sure both width and height have been read correctly. */
    if (returned_value != 2)
    {
        fprintf(stderr, "Error reading image width/height from the .ppm file.\n");

        goto free_memory;
    }

    /* Check if the maximum color value is 255. */
    returned_value = fscanf(pFile, "%d", &id_255);

    if (!(returned_value == 1 && id_255 == max_color_value))
    {
        fprintf(stderr, "Error reading 255 mark in the .ppm file.\n");

        goto free_memory;
    }

    fseek(pFile, 1, SEEK_CUR);

    /* Each pixel consists of 3 bytes for GL_RGB storage. */
    pixels = (char*) calloc(width * height, num_of_bytes_per_pixel);

    if (pixels == NULL)
    {
        fprintf(stderr, "Error allocating memory for pixels buffer.\n");

        goto free_memory;
    }

    /* Load image into the pixel buffer. */
    n_loaded_pixels = fread(pixels, num_of_bytes_per_pixel, width * height, pFile);

    if (n_loaded_pixels != width * height)
    {
        fprintf(stderr, "Error reading .ppm file.\n");

        goto free_memory;
    }

    /* Finally, put all needed info into the Image struct. */
    image.width  = width;
    image.height = height;
    image.pixels = pixels;

free_memory:
    free((void*) line_str);
    line_str = NULL;

return_now:
    return image;
}

#ifdef _WIN32
    #pragma warning(pop)
#endif /* _WIN32 */

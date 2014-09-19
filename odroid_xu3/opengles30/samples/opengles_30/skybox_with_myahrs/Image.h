/*
 * This proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009 - 2013 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef PIXMAP_H
    #define PIXMAP_H

    /**
     * \brief Struct representing texture image.
     */
    typedef struct ImageFile
    {
	/** Width of texture. */
        int   width;
        /** Height of texture. */
        int   height;
        /** Pointer to the pixel data. */
        char* pixels; 
    } ImageFile;

    /** Reads the pixmap file and loads the texture image information into Image struct.
     *
     *  @param ppm_file_name Path to the .ppm file.
     *  @return              Filled TextureImage struct with texture image params and data.
     */
    ImageFile load_ppm_file(const char* ppm_file_name);

#endif /* PIXMAP_H */
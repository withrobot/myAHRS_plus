/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include "ETCHeader.h"

namespace MaliSDK
{
    ETCHeader::ETCHeader()
    {
    
    }

    ETCHeader::ETCHeader(unsigned char *data)
    {
        /*
         * Load from a ETC compressed pkm image file. 
         * First 6 bytes are the name of the file format and version/packing type.
         * Bytes 7 and 8 are blank.
         */
        /* Beware endianess issues with most/least significant bits of the height and width. */
        paddedWidthMSB = data[8];
        paddedWidthLSB = data[9];
        paddedHeightMSB = data[10];
        paddedHeightLSB = data[11];
        widthMSB = data[12];
        widthLSB = data[13];
        heightMSB = data[14];
        heightLSB = data[15];
    }

    unsigned short ETCHeader::getWidth(void)
    {
        return (widthMSB << 8) | widthLSB;
    }

    unsigned short ETCHeader::getHeight(void)
    {
        return (heightMSB << 8) | heightLSB;
    }

    unsigned short ETCHeader::getPaddedWidth(void)
    {
        return (paddedWidthMSB << 8) | paddedWidthLSB;
    }

    unsigned short ETCHeader::getPaddedHeight(void)
    {
        return (paddedHeightMSB << 8) | paddedHeightLSB;
    }

#if GLES_VERSION == 2
    GLsizei ETCHeader::getSize(GLenum internalFormat)
    {
        return (getPaddedWidth() * getPaddedHeight());
    }
#elif GLES_VERSION == 3
    GLsizei ETCHeader::getSize(GLenum internalFormat)
    {
        if (internalFormat != GL_COMPRESSED_RG11_EAC       && internalFormat != GL_COMPRESSED_SIGNED_RG11_EAC &&
            internalFormat != GL_COMPRESSED_RGBA8_ETC2_EAC && internalFormat != GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC)
        {
            return (getPaddedWidth() * getPaddedHeight()) >> 1;
        }
        else
        {
            return (getPaddedWidth() * getPaddedHeight());
        }
    }
#endif
}
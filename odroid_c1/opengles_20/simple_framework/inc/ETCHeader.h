/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
 
#ifndef ETCHEADER_H
#define ETCHEADER_H

#if GLES_VERSION == 2
#include <GLES2/gl2.h>
#elif GLES_VERSION == 3
#include <GLES3/gl3.h>
#else 
#error "GLES_VERSION must be defined as either 2 or 3"
#endif

namespace MaliSDK
{
    /**
     * \brief Class to extract information from the ETC headers of compressed textures.
     */
    class ETCHeader
    {
    private:
        unsigned char paddedWidthMSB;
        unsigned char paddedWidthLSB;
        unsigned char paddedHeightMSB;
        unsigned char paddedHeightLSB;
        unsigned char widthMSB;
        unsigned char widthLSB;
        unsigned char heightMSB;
        unsigned char heightLSB;
    public:
        /**
         * \brief Default constructor.
         */
        ETCHeader();

        /**
         * \brief Extract the ETC header information from a loaded ETC compressed texture.
         */
        ETCHeader(unsigned char *data);
        
        /**
         * \brief The width of the original texture.
         * 
         * The width of a compressed texture is padded to 4x4 blocks by the compression method.
         * The resulting width of the compressed texture may therefore be larger if it's original width was not a multiple of 4.
         * By using the unpadded width, the original texture can be drawn.
         * \return The width of the original texture without padding.
         */
        unsigned short getWidth(void);

        /**
         * \brief The height of the original texture.
         * 
         * The height of a compressed texture is padded to 4x4 blocks by the compression method.
         * The resulting height of the compressed texture may therefore be larger if it's original height was not a multiple of 4.
         * By using the unpadded height, the original texture can be drawn.
         * \return The height of the original texture without padding.
         */
        unsigned short getHeight(void);

        /**
         * \brief The width of the compressed texture with the padding added.
         * 
         * The width of a compressed texture is padded to 4x4 blocks by the compression method.
         * The resulting width of the compressed texture may therefore be larger if it's original width was not a multiple of 4.
         * \return The width of the compressed texture with padding included.
         */
        unsigned short getPaddedWidth(void);

        /**
         * \brief The height of the compressed texture with the padding added.
         * 
         * The height of a compressed texture is padded to 4x4 blocks by the compression method.
         * The resulting height of the compressed texture may therefore be larger if it's original height was not a multiple of 4.
         * \return The height of the compressed texture with padding included.
         */
        unsigned short getPaddedHeight(void);

        /**
         * \brief The size of the compressed texture with the padding added.
         * 
         * The size is computed as padded width multiplied by padded height.
         * \param[in] internalFormat The internal format of the compressed texture.
         * \return The size of the compressed texture with padding included.
         */
        GLsizei getSize(GLenum internalFormat);
    };
}
#endif /* ETCHEADER_H */
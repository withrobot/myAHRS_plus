/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef HDR_IMAGE_LOADER_H
#define HDR_IMAGE_LOADER_H

namespace MaliSDK
{
    /**
     * \brief Class to load an manage HDR images.
     *
     * This class implements a loader for the Picture Radiance format.
     * Will only load HDR images with FORMAT=32-bit_rle_rgbe and coordinates specified in -Y +X.
     * See http://radsite.lbl.gov/radiance/refer/filefmts.pdf for more information.
     */
    class HDRImage
    {
        public:
            /**
             * \brief Default constructor.
             */
            HDRImage(void);

            /**
             * \brief Constructor which loads a HDR image from a file.
             *
             * \param[in] filePath The path to the HDR image to load.
             */
            HDRImage(const std::string& filePath);

            /**
             * \brief Copy constructor to copy the contents of one HDRImage to another.
             *
             * \param[in] another The HDRImage to copy from.
             */
            HDRImage(HDRImage& another);

            /**
             * \brief Destructor.
             */
            virtual ~HDRImage(void);

            /**
             * \brief Load a HDRImage from a file.
             *
             * \param[in] filePath The path to the HDR image to load.
             */
            void loadFromFile(const std::string& filePath);
          
            /**
             * \brief Overloading assignment operater to do deep copy of the HDRImage data.
             *
             * \param[in] another The HDRImage to copy from.
             */
            HDRImage& operator=(const HDRImage &another);

            /**
             * \brief The HDR image data.
             *
             * Data is stored a floating point RBG values for all the pixels.
             * Total size is width * height * 3 floating point values.
             */
            float* rgbData;

            /**
             * \brief The width of the HDR image.
             */
            int width;

            /**
             * \brief The height of the HDR image.
             */
            int height;

        private:

            struct RGBEPixel
            {
                unsigned char r;
                unsigned char g;
                unsigned char b;
                unsigned char e;
            };

            static void convertRGBEPixel(const RGBEPixel& pixel, float* rgbData);

            static float convertSingleComponent(unsigned char value, int exponent);

            static bool decodeLine(FILE* file, int lineLength, RGBEPixel* scanLine);

            static void writeDecodedComponent(int componentIndicator, unsigned char value, RGBEPixel* pixel);
    };

}
#endif


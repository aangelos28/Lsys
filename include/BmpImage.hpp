#pragma once

#include <cstdint>
#include "Canvas.hpp"

namespace lsys::io
{
    /**
     * Represents the header of a BMP file.
     * The size of the header must be 14 bytes.
     */
    #pragma pack(push, 1) // for proper byte alignment
    struct BmpHeader
    {
        uint16_t file_type = 0x4D42; // "BM"
        uint32_t file_size = 0;
        uint32_t reserved = 0;
        uint32_t data_offset = 54;
    };
    #pragma pack(pop)

    /**
     * Number of bits pixels are represented with in a BMP file.
     */
    enum BmpBitsPerPixel : uint16_t
    {
        RGB16 = 16, RGB24 = 24 // Other types not supported
    };

    /**
     * Compression types for a BMP file.
     */
    enum BmpCompression : uint32_t
    {
        BI_RGB = 0 // Compression not supported
    };

    /**
     * Represents the information header of a BMP file.
     * The size of the info header must be 40 bytes.
     */
    #pragma pack(push, 1)
    struct BmpInfoHeader
    {
        uint32_t size = 40;
        uint32_t image_width;
        uint32_t image_height;
        uint16_t num_planes = 1;
        BmpBitsPerPixel bits_per_pixel = BmpBitsPerPixel::RGB24;
        BmpCompression compression = BmpCompression::BI_RGB;
        uint32_t compressed_image_size = 0;
        uint32_t x_pixels_per_m = 0;
        uint32_t y_pixels_per_m = 0;
        uint32_t num_colors_used = 0;
        uint32_t num_important_colors = 0;
    };
    #pragma pack(pop)

    /**
     * Represents a BMP image.
     * Currently, only RGB pixels are supported and no compression is implemented.
     */
    class BmpImage
    {
    public:
        explicit BmpImage(graphics::PixelContainerType pixels, uint16_t width, u_int16_t height);
        BmpImage() = default;

        /**
         * Set the pixel data for the BMP image.
         * The width and height parameters are used to compute and assign header values such as the file size.
         *
         * @param pixels Pixel data array
         * @param width Width fo the pixel array
         * @param height Height of the pixel array
         */
        void setPixels(graphics::PixelContainerType pixels, uint16_t width, u_int16_t height);

        /**
         * Write the BMP image to a file.
         *
         * @param filename Path to the file
         */
        void writeToFile(const std::string& filename);

        [[nodiscard]]
        const BmpHeader& getHeader() const;
        void setHeader(const BmpHeader& header);

        [[nodiscard]]
        const BmpInfoHeader& getInfoHeader() const;
        void setInfoHeader(const BmpInfoHeader& info_header);

        [[nodiscard]]
        graphics::RgbColor* const* getPixels() const;

    private:
        /**
         * Header.
         */
        BmpHeader header;

        /**
         * Information header.
         */
        BmpInfoHeader info_header;

        /**
         * Pixel data.
         */
        graphics::PixelContainerType pixels;

        /**
         * Size of the padding to apply tot he pixel data, if necessary.
        */
        unsigned int padding_size;
    };
}
#include <fstream>
#include "BmpImage.hpp"

namespace lsys::io
{
    BmpImage::BmpImage(graphics::PixelContainerType pixels, uint16_t width, u_int16_t height)
    {
        setPixels(pixels, width, height);
    }

    void BmpImage::setPixels(graphics::PixelContainerType pixels, uint16_t width, u_int16_t height)
    {
        this->pixels = pixels;
        this->info_header.image_width = width;
        this->info_header.image_height = height;

        this->padding_size = (4 - ((width * sizeof(graphics::RgbColor)) % 4)) % 4;
        this->header.file_size = sizeof(header) + sizeof(info_header) + sizeof(graphics::RgbColor) * (width + padding_size) * height;
    }

    void BmpImage::writeToFile(const std::string& filename)
    {
        std::ofstream file;
        file.open(filename, std::ios::trunc | std::ios::binary);

        // Write header
        file.write(reinterpret_cast<char*>(&header), sizeof(header));

        // Write info header
        file.write(reinterpret_cast<char*>(&info_header), sizeof(info_header));

        // Padding
        unsigned char padding[3] = {0, 0, 0};

        // Write pixels
        for (uint32_t y = info_header.image_height - 1; y < info_header.image_height; --y)
        {
            for (uint32_t x = 0; x < info_header.image_width; ++x)
            {
                // Need to reorder pixel color from RGB to BGR
                unsigned char rgb_color[3] = {pixels[y][x].b, pixels[y][x].g, pixels[y][x].r};

                // TODO Per-pixel writing is not the most efficient way to write
                file.write(reinterpret_cast<char*>(&rgb_color), sizeof(graphics::RgbColor));
            }
            file.write(reinterpret_cast<char*>(&padding), padding_size);
        }

        file.flush();
    }

    const BmpHeader& BmpImage::getHeader() const
    {
        return header;
    }

    void BmpImage::setHeader(const BmpHeader& header)
    {
        this->header = header;
    }

    const BmpInfoHeader& BmpImage::getInfoHeader() const
    {
        return info_header;
    }

    void BmpImage::setInfoHeader(const BmpInfoHeader& info_header)
    {
        this->info_header = info_header;
    }

    graphics::RgbColor* const* BmpImage::getPixels() const
    {
        return pixels;
    }
}
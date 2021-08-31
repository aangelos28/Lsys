#pragma once

namespace lsys::graphics
{
    /**
     * Generic 2D vector.
     *
     * @tparam T Type of the vector components
     */
    template<typename T>
    struct Vec2
    {
        T x;
        T y;

        Vec2() = default;

        Vec2(T x, T y) : x(x), y(y)
        {
        }
    };
    using Point2d = Vec2<float>; // Point in 2D space (x, y)
    using Spacing2d = Vec2<float>; // Pixel spacing (x, y)
    using Pixelxy = Vec2<unsigned short>; // Pixel coordinates (row, col)

    /**
     * Bounds of a 2D plane.
     */
    struct Bounds2d
    {
        float min_x;
        float min_y;
        float max_x;
        float max_y;
    };

    /**
     * RGB color .
     */
    struct RgbColor
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;

        RgbColor();

        RgbColor(unsigned char r, unsigned char g, unsigned char b);
    };
    using PixelContainerType = RgbColor**; // Pixel data array type
}
#include <cmath>
#include <iostream>
#include "Canvas.hpp"

namespace lsys::graphics
{
    Canvas::Canvas(const Bounds2d& bounds, unsigned short width, unsigned short height)
        : bounds(bounds)
        , width(width)
        , height(height)
        , allow_drawing(true)
        , pen_down(true)
        , pixels(nullptr)
    {
        spacing.x = (bounds.max_x - bounds.min_x) / (float)width;
        spacing.y = (bounds.max_y - bounds.min_y) / (float)height;
    }

    Canvas::~Canvas()
    {
        // Deallocate pixels if they have been allocated
        if (pixels != nullptr)
        {
            for (unsigned short i = 0; i < height; ++i)
            {
                delete[] pixels[i];
            }
            delete[] pixels;
        }
    }

    Pixelxy Canvas::getPixelFromPoint(Point2d point) const
    {
        auto pixel_x = static_cast<unsigned short>(point.x - bounds.min_x / spacing.x);
        auto pixel_y = static_cast<unsigned short>(point.y - bounds.min_y / spacing.y);

        return Pixelxy(pixel_x, (height - 1) - pixel_y);
    }

    void Canvas::updateBounds(Point2d reference)
    {
        if (reference.x > bounds.max_x)
        {
            bounds.max_x = reference.x;
        }
        else if (reference.x < bounds.min_x)
        {
            bounds.min_x = reference.x;
        }

        if (reference.y > bounds.max_y)
        {
            bounds.max_y = reference.y;
        }
        else if (reference.y < bounds.min_y)
        {
            bounds.min_y = reference.y;
        }
    }

    Point2d Canvas::moveFromPoint(Point2d point, float distance, int angle)
    {
        float radians = angle * M_PI / 180.0;
        point.x += std::cos(radians) * distance;
        point.y += std::sin(radians) * distance;

        return point;
    }

    Point2d Canvas::drawLine(Point2d start, float length, int angle)
    {
        // Need to ensure that the canvas is large enough before drawing line
        updateBounds(start);

        Pixelxy start_pixel = getPixelFromPoint(start);
        Point2d end = moveFromPoint(start, length, angle);
        Pixelxy end_pixel = getPixelFromPoint(end);

        // Need to ensure that the canvas is large enough before drawing line
        updateBounds(end);

        if (this->allow_drawing && this->pen_down)
        {
            rasterizeLine(start_pixel, end_pixel);
        }

        return end;
    }

    void Canvas::rasterizeLine(Pixelxy start, Pixelxy end)
    {
        int dx = std::abs(end.x - start.x);
        int sx = start.x < end.x ? 1 : -1;

        int dy = std::abs(end.y - start.y);
        int sy = start.y < end.y ? 1 : -1;

        int err = (dx > dy ? dx : -dy) / 2;
        int e2;

        while (true)
        {
            pixels[start.y][start.x] = RgbColor(255, 255, 255);

            if (start.x == end.x && start.y == end.y)
                break;

            e2 = err;

            if (e2 > -dx)
            {
                err -= dy;
                start.x += sx;
            }
            if (e2 < dy)
            {
                err += dx;
                start.y += sy;
            }
        }
    }

    void Canvas::penUp()
    {
        this->pen_down = false;
    }

    void Canvas::penDown()
    {
        this->pen_down = true;
    }

    void Canvas::allocatePixels()
    {
        // Update spacing
        spacing.x = (bounds.max_x - bounds.min_x) / (float)width;
        spacing.y = (bounds.max_y - bounds.min_y) / (float)height;

        // Allocate pixels
        pixels = new RgbColor*[height];
        for (unsigned short i = 0; i < height; ++i)
        {
            pixels[i] = new RgbColor[width];
        }
    }

    void Canvas::printCanvasAscii(std::ostream& out) const
    {
        for (unsigned short y = 0; y < height; ++y)
        {
            for (unsigned short x = 0; x < width; ++x)
            {
                out << ((pixels[y][x].r == 255) ? '*' : '.') << " ";
            }
            out << '\n';
        }
        out.flush();
    }

    //////////////////////////////////////////////////////////////

    const Bounds2d& Canvas::getBounds() const
    {
        return bounds;
    }

    void Canvas::setBounds(const Bounds2d& bounds)
    {
        Canvas::bounds = bounds;
    }

    const Spacing2d& Canvas::getSpacing() const
    {
        return spacing;
    }

    void Canvas::setSpacing(const Spacing2d& spacing)
    {
        Canvas::spacing = spacing;
    }

    const PixelContainerType& Canvas::getPixels() const
    {
        return pixels;
    }

    void Canvas::setPixels(const PixelContainerType& pixels)
    {
        Canvas::pixels = pixels;
    }

    bool Canvas::getAllowDrawing() const
    {
        return allow_drawing;
    }

    void Canvas::setAllowDrawing(bool allow_drawing)
    {
        this->allow_drawing = allow_drawing;
    }

    unsigned short Canvas::getWidth() const
    {
        return width;
    }

    void Canvas::setWidth(unsigned short width)
    {
        this->width = width;
    }

    unsigned short Canvas::getHeight() const
    {
        return height;
    }

    void Canvas::setHeight(unsigned short height)
    {
        this->height = height;
    }

    RgbColor::RgbColor()
        : r(0)
        , g(0)
        , b(0)
    {
    }

    RgbColor::RgbColor(unsigned char r, unsigned char g, unsigned char b)
        : r(r)
        , g(g)
        , b(b)
    {
    }
}

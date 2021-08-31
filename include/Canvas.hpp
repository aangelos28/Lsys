#pragma once

#include <memory>
#include "types.hpp"

namespace lsys::graphics
{
    /**
     * Represents a 2D canvas that can be used for drawing graphics.
     * The canvas uses a 2D plane which it discretizes using width x height pixels.
     *
     * The canvas will not store any pixel data until the pixels are allocated after determining
     * the bounds of the 2D plane.
     */
    class Canvas
    {
    public:
        /**
         * Construct a new canvas given the bounds of a 2D plane, as well as the width and height of the discretization.
         *
         * @param bounds Bounds of the 2D plane
         * @param width Width of the discretization in pixels
         * @param height Height of the discretization in pixels
         */
        Canvas(const Bounds2d& bounds, unsigned short width, unsigned short height);
        ~Canvas();

        /**
         * Draw a line of length l with angle d in the canvas starting from a given point.
         * Return the end point of the line.
         *
         * @param start The point from which to start drawing the line
         * @param length The length of the line
         * @param angle The angle at which to draw the line
         *
         * @return End point of the line
         */
        Point2d drawLine(Point2d start, float length, int angle);

        void penUp();
        void penDown();

        /**
         * Allocate pixels for this canvas. Must be called first before any rasterization can happen.
         */
        void allocatePixels();

        /**
         * Print the canvas in ASCII.
         */
        void printCanvasAscii(std::ostream& out) const;

        /////////////////////////////////////////////

        [[nodiscard]]
        const Bounds2d& getBounds() const;
        void setBounds(const Bounds2d& bounds);

        [[nodiscard]]
        unsigned short getWidth() const;
        void setWidth(unsigned short width);

        [[nodiscard]]
        unsigned short getHeight() const;
        void setHeight(unsigned short height);

        [[nodiscard]]
        const Spacing2d& getSpacing() const;
        void setSpacing(const Spacing2d& spacing);

        [[nodiscard]]
        const PixelContainerType& getPixels() const;
        void setPixels(const PixelContainerType& pixels);

        [[nodiscard]]
        bool getAllowDrawing() const;
        void setAllowDrawing(bool allow_drawing);

    private:
        /**
         * Get the closest pixel given a point in the 2D plane.
         *
         * @param point Point in the 2D plane
         * @return Closest pixel to the point
         */
        [[nodiscard]]
        Pixelxy getPixelFromPoint(Point2d point) const;

        /**
         * Update the bounds of the 2D plane to include the reference point.
         *
         * @param reference Point to include in the plane
         */
        void updateBounds(Point2d reference);

        /**
         * Given a point, get a new point at a distance l and an angle d from the point.
         *
         * @param point Point to move from
         * @param distance Distance to move
         * @param angle Angle in which to move
         *
         * @return New point
         */
        static Point2d moveFromPoint(Point2d point, float distance, int angle);

        /**
         * Rasterize a line from pixel a to pixel b.
         * Uses Bresenham's line algorithm.
         *
         * @param start
         * @param end
         */
        void rasterizeLine(Pixelxy start, Pixelxy end);

        ///////////////////////////////

        /**
         * Bounds of the 2D plane.
         */
        Bounds2d bounds;

        /**
         * Spacing of the discretization (pixel data) of the 2D plane.
         */
        Spacing2d spacing;

        /**
         * Width of the canvas (in pixels).
         */
        unsigned short width;

        /**
         * Height of the canvas (in pixels),
         */
        unsigned short height;

        /**
         * Pixels of the canvas.
         */
        PixelContainerType pixels;

        /**
         * Whether a turtle can write to the canvas.
         */
        bool pen_down;

        /**
         * Whether the canvas allows drawing.
         * Overrides pen_down.
         */
        bool allow_drawing;
    };
}

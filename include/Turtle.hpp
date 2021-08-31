#pragma once

#include <vector>
#include <stack>
#include "Canvas.hpp"
#include "TurtleCommand.hpp"

namespace lsys
{
    using namespace graphics;

    /**
     * Represents a position and rotation in 2D
     */
    struct Transform2d
    {
        Point2d position; // x, y
        int rotation; // degrees
    };

    /**
     * Represents a turtle in a 2D plane. Contains a 2D canvas for drawing.
     */
    class Turtle
    {
    public:
        /**
         * Construct a new turtle with the given transform associated with the given canvas.
         *
         * @param transform The initial transform of the turtle
         * @param canvas The canvas the turtle exists on
         */
        Turtle(const Transform2d& transform, Canvas& canvas);

        /**
         * Execute a full cycle of a turtle program.
         * First perform a dry run to estimate plane bounds, then do a second run drawing the results.
         */
        void run();

        /**
         * Execute all turtle commands in the queue.
         * Must ensure that the canvas has proper bounds before drawing.
         */
        void executeCommands();
        void executeCommandsDebug();

        /**
         * Clear all commands currently in the turtle's queue
         */
        void clearCommands();

        /////////////////////////////////////////////
        // Turtle Commands
        /////////////////////////////////////////////
        /**
         * Move the turtle x units forward.
         *
         * @param distance The x distance to move the turtle forward
         */
        void moveForward(float distance);

        /**
         * Turn the turtle d degrees in reference to the unit circle. Turns left if positive, right if negative.
         *
         * @param degrees Degrees to turn turtle. Left if positive, right if negative.
         */
        void turn(int degrees);

        /**
         * Push the current transform of the turtle to the transform stack.
         */
        void pushState();

        /**
         * Pop the top transform of the turtle in the stack.
         * Sets this transform as the turtle's current transform.
         */
        void popState();

        /**
         * Stop the turtle from drawing wherever it goes.
         */
        void penUp();

        /**
         * Allow the turtle to draw wherever it goes.
         */
        void penDown();

        /////////////////////////////////////////////

        [[nodiscard]]
        const Transform2d& getTransform() const;
        void setTransform(const Transform2d& transform);

        [[nodiscard]]
        Canvas& getCanvas() const;
        void setCanvas(Canvas& canvas);

        [[nodiscard]]
        size_t getTotalCommands() const;

        /**
         * Print the current transform of the turtle.
         */
        void printTurtleTransform() const;

    private:
        /**
         * The turtle's transform.
         */
        Transform2d transform;

        /**
         * The turtle's initially assigned transform.
         */
        Transform2d initialTransform;

        /**
         * Queue of commands to execute for the turtle.
         */
        std::vector<std::unique_ptr<TurtleCommand>> command_queue;

        /**
         * Stack containing stored transforms for push/pop commands.
         */
        std::stack<Transform2d> transformStack;

        /**
         * The canvas the turtle exists on.
         */
        Canvas& canvas;

        friend MoveForwardCommand;
        friend TurnCommand;
        friend PushStateCommand;
        friend PopStateCommand;
    };
}

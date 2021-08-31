#pragma once

namespace lsys
{
    class Turtle;

    /**
     * Base for a turtle command.
     * A command is executed by the turtle by calling its "execute" function.
     */
    struct TurtleCommand
    {
        virtual void execute(Turtle& turtle) = 0;
    };

    /**
     * Command for moving the turtle forward d units.
     */
    struct MoveForwardCommand : TurtleCommand
    {
        /**
         * Distance to move forward.
         */
        float distance;

        void execute(Turtle& turtle) override;

        explicit MoveForwardCommand(float distance);
    };

    /**
     * Command for turning the turtle d degrees.
     */
    struct TurnCommand : TurtleCommand
    {
        /**
         * Degrees to turn.
         */
        int degrees;

        void execute(Turtle& turtle) override;

        explicit TurnCommand(int degrees);
    };

    /**
     * Command for pushing the state of the turtle to the stack.
     */
    struct PushStateCommand : TurtleCommand
    {
        void execute(Turtle& turtle) override;
    };

    /**
     * Command for popping the state of the turtle from the stack.
     */
    struct PopStateCommand : TurtleCommand
    {
        void execute(Turtle& turtle) override;
    };

    /**
     * Command for stopping a turtle from drawing a trail.
     */
    struct PenUpCommand : TurtleCommand
    {
        void execute(Turtle& turtle) override;
    };

    /**
     * Command for allowing a turtle to draw a trail.
     */
    struct PenDownCommand : TurtleCommand
    {
        void execute(Turtle& turtle) override;
    };
}

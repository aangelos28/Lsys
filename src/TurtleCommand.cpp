#include <TurtleCommand.hpp>
#include <Turtle.hpp>

namespace lsys
{
    MoveForwardCommand::MoveForwardCommand(float distance)
        : distance(distance)
    {
    }

    TurnCommand::TurnCommand(int degrees)
        : degrees(degrees)
    {
    }

    void MoveForwardCommand::execute(Turtle& turtle)
    {
        Point2d end = turtle.canvas.drawLine(turtle.transform.position, distance, turtle.transform.rotation);
        turtle.transform.position = end;
    }

    void TurnCommand::execute(Turtle& turtle)
    {
        turtle.transform.rotation = (turtle.transform.rotation + degrees) % 360;
    }

    void PushStateCommand::execute(Turtle& turtle)
    {
        turtle.transformStack.push(turtle.transform);
    }

    void PopStateCommand::execute(Turtle& turtle)
    {
        if (turtle.transformStack.empty()) return;

        turtle.transform = turtle.transformStack.top();
        turtle.transformStack.pop();
    }

    void PenUpCommand::execute(Turtle& turtle)
    {
        turtle.getCanvas().penUp();
    }

    void PenDownCommand::execute(Turtle& turtle)
    {
        turtle.getCanvas().penDown();
    }
}


#include <iostream>
#include "Turtle.hpp"

namespace lsys
{
    Turtle::Turtle(const Transform2d& transform, Canvas& canvas)
        : transform(transform)
        , initial_transform(transform)
        , canvas(canvas)
    {
    }

    void Turtle::run()
    {
        // Do a dry run to estimate canvas bounds
        canvas.setAllowDrawing(false);
        executeCommands();
        canvas.setAllowDrawing(true);

        // Restore the transform of the turtle
        transform = initial_transform;

        // Now run and rasterize
        canvas.allocatePixels();
        executeCommands();
    }

    void Turtle::executeCommands()
    {
        // Execute all commands
        for (const auto& i : command_queue)
        {
            i->execute(*this);
        }
    }

    #if 0
    void Turtle::executeCommandsDebug()
    {
        // Execute all commands
        for (const auto& i : command_queue)
        {
            i->execute(*this);
            printTurtleTransform();
            canvas.printCanvasAscii();
            std::cout << "\n\n";
        }
    }
    #endif

    void Turtle::clearCommands()
    {
        command_queue.clear();
    }

    void Turtle::resetTransform()
    {
        this->transform = initial_transform;
    }

    void Turtle::moveForward(float distance)
    {
        command_queue.push_back(std::make_shared<MoveForwardCommand>(distance));
    }

    void Turtle::turn(int degrees)
    {
        command_queue.push_back(std::make_shared<TurnCommand>(degrees));
    }

    void Turtle::pushState()
    {
        command_queue.push_back(std::make_shared<PushStateCommand>());
    }

    void Turtle::popState()
    {
        command_queue.push_back(std::make_shared<PopStateCommand>());
    }

    void Turtle::penUp()
    {
        command_queue.push_back(std::make_shared<PenUpCommand>());
    }

    void Turtle::penDown()
    {
        command_queue.push_back(std::make_shared<PenDownCommand>());
    }

    void Turtle::addCommand(const std::shared_ptr<TurtleCommand>& command)
    {
        command_queue.push_back(command);
    }

    //////////////////////////////////////////////////////////////

    const Transform2d& Turtle::getTransform() const
    {
        return transform;
    }

    void Turtle::setTransform(const Transform2d& transform)
    {
        this->transform = transform;
    }

    Canvas& Turtle::getCanvas() const
    {
        return canvas;
    }

    void Turtle::setCanvas(Canvas& canvas)
    {
        this->canvas = canvas;
    }

    size_t Turtle::getTotalCommands() const
    {
        return command_queue.size();
    }

    void Turtle::printTurtleTransform() const
    {
        std::cout << "Turtle Position: {" << transform.position.x << ", " << transform.position.y << "}" << '\n';
        std::cout << "Turtle Rotation: " << transform.rotation << '\n';
    }
}

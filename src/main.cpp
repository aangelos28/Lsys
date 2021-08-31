#include <iostream>
#include "Canvas.hpp"
#include "Turtle.hpp"
#include "BmpImage.hpp"

int main()
{
    std::cout << "Turtle program" << std::endl;

    lsys::Canvas canvas({0, 0, 0, 0}, 400, 400);
    lsys::Turtle turtle({{201, 0}, 0}, canvas);

    // Draw a simple Y with the turtle
    turtle.turn(90);
    turtle.penUp();
    turtle.moveForward(100);
    turtle.penDown();
    turtle.moveForward(80);
    turtle.pushState();
    turtle.turn(30);
    turtle.moveForward(50);
    turtle.popState();
    turtle.turn(-30);
    turtle.moveForward(50);

    turtle.run();

    // Write turtle canvas as a BMP image
    lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
    output_image.writeToFile("output.bmp");

    return 0;
}

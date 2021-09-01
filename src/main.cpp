#include <iostream>
#include <Lsystem.hpp>
#include "Canvas.hpp"
#include "Turtle.hpp"
#include "BmpImage.hpp"

void drawTurtleY()
{
    lsys::Canvas canvas({0, 0, 0, 0}, 1000, 1000);
    lsys::Turtle turtle({{500, 0}, 0}, canvas);

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
}

void drawBinaryFractal()
{
    lsys::Canvas canvas({0, 0, 0, 0}, 5000, 5000);
    lsys::Turtle turtle({{2500, 0}, 90}, canvas);

    lsys::Lsystem lsystem;
    lsystem.setAxiom("0");
    lsystem.addSymbol('0', nullptr);
    lsystem.addSymbol('1', std::make_shared<lsys::MoveForwardCommand>(5));
    lsystem.addSymbol('[', std::make_shared<lsys::PushStateCommand>());
    lsystem.addSymbol(']', std::make_shared<lsys::PopStateCommand>());
    lsystem.addSymbol('+', std::make_shared<lsys::TurnCommand>(45));
    lsystem.addSymbol('-', std::make_shared<lsys::TurnCommand>(-45));
    lsystem.addRule('0', "1[+0]-0");
    lsystem.addRule('1', "11");

    lsystem.iterate(10);
    std::cout << lsystem.getIteratedAxiom() << '\n';

    lsystem.evaluate(turtle);

    // Write turtle canvas as a BMP image
    lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
    output_image.writeToFile("output.bmp");
}

void drawKochCurve()
{
    lsys::Canvas canvas({0, 0, 0, 0}, 11000, 6000);
    lsys::Turtle turtle({{50, 50}, 0}, canvas);

    lsys::Lsystem lsystem;
    lsystem.setAxiom("F");
    lsystem.addSymbol('F', std::make_shared<lsys::MoveForwardCommand>(5));
    lsystem.addSymbol('+', std::make_shared<lsys::TurnCommand>(90));
    lsystem.addSymbol('-', std::make_shared<lsys::TurnCommand>(-90));
    lsystem.addRule('F', "F+F-F-F+F");

    lsystem.iterate(7);
    std::cout << lsystem.getIteratedAxiom() << '\n';

    lsystem.evaluate(turtle);

    // Write turtle canvas as a BMP image
    lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
    output_image.writeToFile("output.bmp");
}

void drawSierpinskiTriangle()
{
    lsys::Canvas canvas({0, 0, 0, 0}, 3000, 3000);
    lsys::Turtle turtle({{200, 200}, 120}, canvas);

    lsys::Lsystem lsystem;
    lsystem.setAxiom("F-G-G");
    lsystem.addSymbol('F', std::make_shared<lsys::MoveForwardCommand>(20));
    lsystem.addSymbol('G', std::make_shared<lsys::MoveForwardCommand>(20));
    lsystem.addSymbol('+', std::make_shared<lsys::TurnCommand>(120));
    lsystem.addSymbol('-', std::make_shared<lsys::TurnCommand>(-120));
    lsystem.addRule('F', "F-G+F+G-F");
    lsystem.addRule('G', "GG");

    lsystem.iterate(7);
    std::cout << lsystem.getIteratedAxiom() << '\n';

    lsystem.evaluate(turtle);

    // Write turtle canvas as a BMP image
    lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
    output_image.writeToFile("output.bmp");
}

int main()
{
    std::cout << "Turtle program" << std::endl;

    //drawTurtleY();
    //drawBinaryFractal();
    //drawKochCurve();
    drawSierpinskiTriangle();

    return 0;
}

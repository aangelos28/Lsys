#include <iostream>
#include <Lsystem.hpp>
#include "Canvas.hpp"
#include "Turtle.hpp"
#include "BmpImage.hpp"

void drawTurtleTriangle()
{
    lsys::Canvas canvas({0, 0, 0, 0}, 1000, 600);
    lsys::Turtle turtle({{250, 100}, 0}, canvas);

    // Draw an isosceles triangle with the turtle
    turtle.moveForward(499);
    turtle.turn(120);
    turtle.moveForward(500);
    turtle.turn(120);
    turtle.moveForward(499);

    turtle.run();

    // Write turtle canvas as a BMP image
    lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
    output_image.writeToFile("turtletriangle.bmp");
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
    lsystem.evaluate(turtle);

    // Write turtle canvas as a BMP image
    lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
    output_image.writeToFile("binaryfractal.bmp");
}

void drawKochCurve()
{
    lsys::Canvas canvas({0, 0, 0, 0}, 3800, 2000);
    lsys::Turtle turtle({{50, 50}, 0}, canvas);

    lsys::Lsystem lsystem;
    lsystem.setAxiom("F");
    lsystem.addSymbol('F', std::make_shared<lsys::MoveForwardCommand>(5));
    lsystem.addSymbol('+', std::make_shared<lsys::TurnCommand>(90));
    lsystem.addSymbol('-', std::make_shared<lsys::TurnCommand>(-90));
    lsystem.addRule('F', "F+F-F-F+F");

    lsystem.iterate(6);
    lsystem.evaluate(turtle);

    // Write turtle canvas as a BMP image
    lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
    output_image.writeToFile("kochcurve.bmp");
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
    lsystem.evaluate(turtle);

    // Write turtle canvas as a BMP image
    lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
    output_image.writeToFile("sierpinskitriangle.bmp");
}

void drawFractalPlant()
{
    lsys::Canvas canvas({0, 0, 0, 0}, 3000, 3000);
    lsys::Turtle turtle({{400, 50}, 60}, canvas);

    lsys::Lsystem lsystem;
    lsystem.setAxiom("X");
    lsystem.addSymbol('X', nullptr);
    lsystem.addSymbol('F', std::make_shared<lsys::MoveForwardCommand>(15));
    lsystem.addSymbol('+', std::make_shared<lsys::TurnCommand>(25));
    lsystem.addSymbol('-', std::make_shared<lsys::TurnCommand>(-25));
    lsystem.addSymbol('[', std::make_shared<lsys::PushStateCommand>());
    lsystem.addSymbol(']', std::make_shared<lsys::PopStateCommand>());
    lsystem.addRule('X', "F+[[X]-X]-F[-FX]+X");
    lsystem.addRule('F', "FF");

    lsystem.iterate(6);
    lsystem.evaluate(turtle);

    // Write turtle canvas as a BMP image
    lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
    output_image.writeToFile("fractalplant.bmp");
}

int main()
{
    std::cout << "Lsys" << std::endl;
    std::cout << "Generating images..." << std::endl;

    drawTurtleTriangle();
    drawBinaryFractal();
    drawKochCurve();
    drawSierpinskiTriangle();
    drawFractalPlant();

    std::cout << "\nDone." << std::endl;

    return 0;
}

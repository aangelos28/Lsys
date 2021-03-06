# Lsys

Simple L-system and turtle graphics C++ library.

---
L-system example (Sierpinski triangle):

![TurtleTriangle](images/sierpinski_triangle.png)
```cpp
// Create 3000x3000 pixel canvas
lsys::Canvas canvas({0, 0, 0, 0}, 3000, 3000);

// Create turtle at position 200, 200 with a rotation of 120 degrees
lsys::Turtle turtle({{200, 200}, 120}, canvas);

lsys::Lsystem lsystem;
lsystem.setAxiom("F-G-G");
lsystem.addSymbol('F', std::make_shared<lsys::MoveForwardCommand>(20));
lsystem.addSymbol('G', std::make_shared<lsys::MoveForwardCommand>(20));
lsystem.addSymbol('+', std::make_shared<lsys::TurnCommand>(120));
lsystem.addSymbol('-', std::make_shared<lsys::TurnCommand>(-120));
lsystem.addRule('F', "F-G+F+G-F");
lsystem.addRule('G', "GG");

// Recursively evaluate L-system 7 times
lsystem.evaluate(7);
    
// Draw L-system with turtle
lsystem.draw(turtle);

// Write turtle canvas as a BMP image
lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
output_image.writeToFile("sierpinski_triangle.bmp");
```
---
Turtle graphics example (equilateral triangle):

![TurtleTriangle](images/turtle_triangle.png)
```cpp
// Create 1000x600 canvas
lsys::Canvas canvas({0, 0, 0, 0}, 1000, 600);

// Create turtle at position 250,100, with a rotation of 0 degrees
lsys::Turtle turtle({{250, 100}, 0}, canvas);

turtle.moveForward(499);
turtle.turn(120);
turtle.moveForward(500);
turtle.turn(120);
turtle.moveForward(499);

// Execute turtle commands
turtle.run();

// Write turtle canvas as a BMP image
lsys::io::BmpImage output_image(turtle.getCanvas().getPixels(), turtle.getCanvas().getWidth(), turtle.getCanvas().getHeight());
output_image.writeToFile("turtle_triangle.bmp");
```

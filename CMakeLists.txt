cmake_minimum_required(VERSION 3.19)
project(Lsys)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(LSYS_SOURCE_LIST
        src/main.cpp src/Turtle.cpp include/Turtle.hpp src/Canvas.cpp include/Canvas.hpp src/TurtleCommand.cpp src/BmpImage.cpp src/Lsystem.cpp)

include_directories(include)

add_executable(lsys ${LSYS_SOURCE_LIST})

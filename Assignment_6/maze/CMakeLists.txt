cmake_minimum_required(VERSION 3.0.0)
project(maze VERSION 0.1.0)

# Add your source files
set(SOURCES
    maze_impl_student.cpp
    maze_impl.cpp
    maze_main.cpp
)

# Add the executable target
add_executable(maze ${SOURCES})

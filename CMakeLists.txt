cmake_minimum_required(VERSION 3.10)

# set the project name
project(renderer)

file(GLOB SOURCES "src/*.cpp")
set(EXECUTABLE_OUTPUT_PATH "build")

# add the executable
add_executable(renderer ${SOURCES})
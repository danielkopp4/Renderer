cmake_minimum_required(VERSION 3.10)

# set the project name
project(renderer)

set (CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp")
set(EXECUTABLE_OUTPUT_PATH "build")

# add the executable
add_executable(renderer ${SOURCES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(renderer PRIVATE Threads::Threads)
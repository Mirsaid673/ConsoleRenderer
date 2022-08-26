cmake_minimum_required(VERSION 3.0.0)
project(ConsoleRenderer VERSION 0.1.0)

set(INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDE "include/*.h")

add_executable(ConsoleRenderer ${SOURCES} ${INCLUDE})
target_include_directories(ConsoleRenderer PRIVATE ${INCLUDE_DIRECTORY})
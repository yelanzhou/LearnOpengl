cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(OpenGL)
cmake_policy(SET CMP0043 NEW)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_definitions("-std=c++11")


file(GLOB SOURCES_FILES *.cpp SOURCES_FILES *.c)
file(GLOB HEADER_FILES *.h)


LINK_DIRECTORIES("D:/Opengl/thirdLib/Release/GLFW/lib")
include_directories("D:/Opengl/thirdLib/Release/GLFW/include")
add_executable(OpenGL ${SOURCES_FILES} ${HEADER_FILES})
target_link_libraries(OpenGL glfw3 opengl32 assimp-vc141-mt)

#target_link_libraries(OpenGL opengl32 glfw3.lib)

#include_directories(./thirdLib)

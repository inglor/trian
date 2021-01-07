cmake_minimum_required(VERSION 3.17)
project(trian)

set(CMAKE_CXX_STANDARD 17)

set(OpenGlLinkers -lglut -lGLU -lGL)

add_executable(trian main.cc Vertex.cc Vertex.hh Edge.cc Edge.hh Triangle.cc Triangle.hh Mesh.cc Mesh.hh Trian.cc Trian.hh Functions.hh)

target_link_libraries(trian ${OpenGlLinkers}) # linking opengl libraries to the project

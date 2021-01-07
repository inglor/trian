cmake_minimum_required(VERSION 3.17)
project(trian)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB SRCS *.cc)

add_executable(trian ${SRCS})

target_link_libraries(trian ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

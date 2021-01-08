cmake_minimum_required(VERSION 3.17)
project(trian)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
message(STATUS "OpenGL found at '${OPENGL_INCLUDE_DIR}' will link with '${OPENGL_LIBRARIES}'")
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_libraries(${OPENGL_LIBRARIES})
endif ()

find_package(GLUT REQUIRED)
message(STATUS "GLUT found at '${GLUT_INCLUDE_DIR}' will link with '${GLUT_LIBRARIES}'")
if (GLUT_FOUND)
    include_directories(${GLUT_INCLUDE_DIR})
    link_libraries(${GLUT_LIBRARIES})
endif ()

find_package(GLEW REQUIRED)
message(STATUS "GLEW found at '${GLUT_INCLUDE_DIR}' will link with '${GLEW_LIBRARIES}'")
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
    link_libraries(${GLEW_LIBRARIES})
endif ()

find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SRCS src/*.cc)

add_executable(trian ${SRCS})

target_link_libraries(trian glfw)

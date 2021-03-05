cmake_minimum_required(VERSION 3.16)
project(trian
	DESCRIPTION "inglor's Delaunay triangulation"
	HOMEPAGE_URL "https://github.com/inglor/trian"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

#NIKOS:
#       Setting compiler options by hand is not the CMake way but it is the only way I know for these options
#       Even so, the "clean" way is per target, but this is enough for this project.
if( CMAKE_CXX_COMPILER_ID MATCHES "GNU"  OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	message(STATUS "GCC/Clang detected, setting stricter than default warning flags")
	list(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	message(STATUS "MS Visual Studio, setting stricter than default warning flags")
	list(APPEND CMAKE_CXX_FLAGS "/Wall /Za")
endif()

# Set the possible values of build type for cmake-gui
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to Debug as none was specified.")
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
endif()

# Optionally enable link time optimization (LTO) by adding the `-flto` flag.
# This provides smaller, faster executables/DSOs, and improves GCC
# diagnostics.
include(CheckIPOSupported)
check_ipo_supported(RESULT LTOAvailable)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
message(STATUS "OpenGL found at '${OPENGL_INCLUDE_DIR}' will link with '${OPENGL_LIBRARIES}'")

find_package(GLUT REQUIRED)
message(STATUS "GLUT found at '${GLUT_INCLUDE_DIR}' will link with '${GLUT_LIBRARIES}'")

find_package(GLEW REQUIRED)
message(STATUS "GLEW found at '${GLUT_INCLUDE_DIR}' will link with '${GLEW_LIBRARIES}'")

find_package(glfw3 REQUIRED)

#NIKOS: might soon be usefull find_package(OpenMP)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)

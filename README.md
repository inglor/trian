# Triangulation

Table of Contents
=================
* [Triangulation](#triangulation)
    * [Description](#description)
    * [Building](#building)
        * [with Docker](#with-docker)
        * [with Native packages](#with-native-packages)
            * [Dependencies](#dependencies)
            * [Build](#build)
    * [Contribute](#contribute)

## Description
The code works in a set of points in 3D space. Assuming these belong in a 
[Delaunay Triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation)
the code performs a 
[Bower & Watson](https://en.wikipedia.org/wiki/Bowyer%E2%80%93Watson_algorithm)
algorithm to create a mesh of triangles and represent it in 3D space using
OpenGL shaders

## Building 
### with Docker
A Dockerfile is provide for compilation. To use it (provided docker daemon is
running)

_Note: The docker will only build the project - it won't expose it locally - 
you need to adjust the `Dockerfile` for copying it locally_
```shell
docker build .
```
### with Native packages
#### Dependencies
- cmake >= 3.11
- C++ compiler supporting C++ Standard 17
- OpenGL
- GLUT
- GLEW
- glfw3

#### Build
Build using cmake in a clean directory
```shell
mkdir build 
cd build
cmake ../
make
./trian
```

## Contribute
Issues and PRs are welcome in GitHub repo https://github.com/inglor/trian

_Note: Before committing make sure you setup the git pre commit hook (only 
done once locally)_
```shell
./setup-hook.sh
```

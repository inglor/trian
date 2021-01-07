#include "Triangle.hh"

Triangle::Triangle() { vertex_x = vertex_y = vertex_z = nullptr; }

Triangle::Triangle(Vertex *x, Vertex *y, Vertex *z) {
  vertex_x = x;
  vertex_y = y;
  vertex_z = z;
}

Triangle::~Triangle() = default;
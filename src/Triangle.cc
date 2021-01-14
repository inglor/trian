#include "Triangle.hh"

std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
  os << "(" << triangle.vertices[0] << ", " << triangle.vertices[1] << ", "
     << triangle.vertices[2] << ")";
  return os;
}
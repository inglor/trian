#include "Vertex.hh"

std::ostream& operator<<(std::ostream& os, const Vertex& vx) {
  os << "(" << vx[0] << ", " << vx[1] << ", " << vx[2] << ")";
  return os;
}

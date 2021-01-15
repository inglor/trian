#include "Triangle.hh"

#include "Edge.hh"

std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
  os << "(" << triangle.vertices[0] << ", " << triangle.vertices[1] << ", "
     << triangle.vertices[2] << ")";
  return os;
}
Triangle::Triangle(Vertex x, Vertex y, Vertex z) : vertices{x, y, z} {
  Edge a = Edge(x, y);
  Edge b = Edge(y, z);
  Edge c = Edge(x, x);
  //  r = a*b*c / sqrt (a+b+c -a+b+c a-b+c a+b-c)
  circumradius = (a.Size() * b.Size() * c.Size()) /
                 std::sqrt((a.Size() + b.Size() + c.Size()) *
                           (-a.Size() + b.Size() + c.Size()) *
                           (a.Size() - b.Size() + c.Size()) *
                           (a.Size() + b.Size() - c.Size()));
  // TODO need to find circumcenter with coords - I think.
}

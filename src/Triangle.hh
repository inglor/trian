#ifndef TRIAN_TRIANGLE_HH
#define TRIAN_TRIANGLE_HH

#include "Vertex.hh"

class Triangle {
 public:
  Triangle(Vertex x, Vertex y, Vertex z) : vertices{x, y, z} {};
  friend std::ostream& operator<<(std::ostream&, const Triangle&);

 private:
  Vertex vertices[3];
};

#endif  // TRIAN_TRIANGLE_HH

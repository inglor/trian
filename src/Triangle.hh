#pragma once

#include "Vertex.hh"

class Triangle {
 public:
  Triangle(Vertex x, Vertex y, Vertex z);
  friend std::ostream& operator<<(std::ostream&, const Triangle&);

 private:
  Vertex vertices[3];
  float circumradius;
};

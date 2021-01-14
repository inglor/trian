#pragma once

#include <iostream>

class Vertex {
 public:
  Vertex(float x, float y, float z) : coords{x, y, z} {};

  float operator[](int i) const { return coords[i]; }
  float& operator[](int i) { return coords[i]; }

  friend std::ostream& operator<<(std::ostream&, const Vertex&);

 private:
  float coords[3] = {0., 0., 0.};
};

#include <iostream>
#include "Vertex.hh"

Vertex::Vertex() = default;

Vertex::Vertex(float x, float y) {
  coords.push_back(x);
  coords.push_back(y);
}

Vertex::Vertex(float x, float y, float z) {
  coords.push_back(x);
  coords.push_back(y);
  coords.push_back(z);
}

void Vertex::Trian_Vertex_show_coords() {
  coords_iterator = coords.begin();
  std::cout << "Coords:" << std::endl;

  while (coords_iterator != coords.end()) {
    std::cout << "v[" << "]\t";
    coords_iterator++;
  }
  std::cout << std::endl;
}

float Vertex::Trian_Vertex_Get_Float(int dimen) {
  return coords[dimen];
}

Vertex::~Vertex() = default;
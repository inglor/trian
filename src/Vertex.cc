#include "Vertex.hh"

#include <iostream>

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
  std::cout << "Coords: ";
  while (coords_iterator != coords.end()) {
    std::cout << "v[" << *coords_iterator << "]\t";
    coords_iterator++;
  }
  std::cout << std::endl;
}

float Vertex::Trian_Vertex_Get_Float(int dimen) { return coords[dimen]; }

Vertex::~Vertex() = default;
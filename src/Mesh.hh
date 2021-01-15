#pragma once

#include <vector>

#include "LibConsts.hh"
#include "Triangle.hh"
#include "Vertex.hh"

const auto compare_x = [](const Vertex &v1, const Vertex &v2) {
  return v1[COORD_X_INDEX] < v2[COORD_X_INDEX];
};
const auto compare_y = [](const Vertex &v1, const Vertex &v2) {
  return v1[COORD_Y_INDEX] < v2[COORD_Y_INDEX];
};

class Mesh {
 public:
  explicit Mesh(int);
  explicit Mesh(FILE *);

  void SaveToFile(FILE *);
  void PrintFirstN(size_t N = 10);
  void Triangulate2D();

 private:
  void Init_Random_Values(size_t);

  std::vector<Vertex> pool;
};

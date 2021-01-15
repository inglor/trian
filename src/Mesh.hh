#pragma once

#include <vector>

#include "Triangle.hh"
#include "Vertex.hh"

static const float MAX_VERTEX_FLOAT = 10.0f;
static const float MIN_VERTEX_FLOAT = -10.0f;
static const int COORD_X_INDEX = 0;
static const int COORD_Y_INDEX = 1;
static const int COORD_Z_INDEX = 2;

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

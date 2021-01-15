#pragma once

#include "LibConsts.hh"
#include "Vertex.hh"
#include "cmath"

class Edge {
 public:
  Edge(const Vertex &v1, const Vertex &v2) : v1(v1), v2(v2) {}
  float Size();

 private:
  Vertex v1;
  Vertex v2;
};

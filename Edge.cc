#include "Edge.hh"

using namespace std;

Edge::Edge() {
  vertex_x = vertex_y = nullptr;
}

Edge::Edge(Vertex *x, Vertex *y) {
  vertex_x = x;
  vertex_y = y;
}

Edge::~Edge() = default;
#ifndef TRIAN_EDGE_HH
#define TRIAN_EDGE_HH

#include "Vertex.hh"

class Edge {
 public:
  Edge();

  Edge(Vertex *, Vertex *);

  virtual ~Edge();

 private:
  Vertex *vertex_x;
  Vertex *vertex_y;
};

#endif  // TRIAN_EDGE_HH

#ifndef TRIAN_TRIANGLE_HH
#define TRIAN_TRIANGLE_HH

#include "Vertex.hh"

using namespace std;

class Triangle {
 public:
  Triangle();

  Triangle(Vertex *, Vertex *, Vertex *);

  virtual ~Triangle();

 private:
  Vertex *vertex_x;
  Vertex *vertex_y;
  Vertex *vertex_z;
};

#endif  // TRIAN_TRIANGLE_HH

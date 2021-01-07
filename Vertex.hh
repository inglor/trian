#ifndef TRIAN_VERTEX_HH
#define TRIAN_VERTEX_HH

#include <cstdio>
#include <vector>

using namespace std;

class Vertex {
 public:
  Vertex();

  Vertex(float, float);

  Vertex(float, float, float);

  void Trian_Vertex_show_coords();

  virtual ~Vertex();

  float Trian_Vertex_Get_Float(int);

 private:
  std::vector<float> coords;
  std::vector<float>::iterator coords_iterator;
};

#endif  // TRIAN_VERTEX_HH

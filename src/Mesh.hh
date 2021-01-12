#ifndef TRIAN_MESH_HH
#define TRIAN_MESH_HH

#include <vector>

#include "Vertex.hh"

class Mesh {
 public:
  explicit Mesh(int);
  explicit Mesh(FILE *);

  void SaveToFile(FILE *);
  void PrintFirstN(size_t N = 10);

 private:
  void Init_Random_Values(size_t);

  std::vector<Vertex> pool;
};

#endif  // TRIAN_MESH_HH

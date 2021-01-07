#ifndef TRIAN_MESH_HH
#define TRIAN_MESH_HH

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Triangle.hh"
#include "Functions.hh"

using namespace std;

class Mesh {
public:
  Mesh();

  explicit Mesh(FILE *);

  Mesh(int, bool);

  virtual ~Mesh();

  int Trian_Mesh_Save_Dataset(FILE *);

  void Trian_Mesh_ShowPool();

private:
  void Trian_Mesh_RandPool();

  Vertex **pool;
  int pool_size;
};


#endif //TRIAN_MESH_HH

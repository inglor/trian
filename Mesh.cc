#include "Mesh.hh"

using namespace std;

Mesh::Mesh() {
  pool = nullptr;
  pool_size = 0;
}

Mesh::Mesh(FILE *input_file) {
  pool = nullptr;
  pool_size = 0;

  fread((void *) &pool_size, sizeof(pool_size), 1, input_file);
  cout << "Pool size read: " << pool_size << std::endl;
  pool = new Vertex *[pool_size];

  float buffer[3 * 1024];
  float c = 0;
  int cp = pool_size;
  // int read=0;
  while (cp) {
    cp--;
    if (c == 0) {
      c = fread((void *) buffer, sizeof(float), 3 * 1024, input_file);
    }
    for (int i = 1; i < 3; i++) {
      cout << "v:" << buffer[i] << std::endl;
    }
    c--;
  }
}

Mesh::Mesh(int size, bool temp) {
  pool = new Vertex *[size];
  pool_size = size;
  Trian_Mesh_RandPool();
}

int Mesh::Trian_Mesh_Save_Dataset(FILE *f) {
  float buffer[3 * 1024];

  fwrite((void *) &pool_size, sizeof(pool_size), 1, f);
  int cp = pool_size;
  int c = 0;
  while (cp) {
    cp--;
    buffer[c] = pool[cp]->Trian_Vertex_Get_Float(0);
    c++;
    buffer[c] = pool[cp]->Trian_Vertex_Get_Float(1);
    c++;
    buffer[c] = pool[cp]->Trian_Vertex_Get_Float(2);
    c++;
    if (c == 3 * 1024 || cp == 0) {
      fwrite((void *) buffer, sizeof(float), c, f);
      c = 0;
    }
  }
  return 0;
}

Mesh::~Mesh() {
  for (int i = 0; i < pool_size; i++) {
    if (pool[i]) {
      delete pool[i];
    }
  }
  delete pool;
}

void Mesh::Trian_Mesh_RandPool() {
  for (int i = 0; i < pool_size; i++) {
    pool[i] = new Vertex(trian::Random_Float_Between(0.0, 10.0),
                         trian::Random_Float_Between(0.0, 10.0),
                         trian::Random_Float_Between(0.0, 10.0));
  }
}

void Mesh::Trian_Mesh_ShowPool() {
  for (int i = 0; i < pool_size && i < 10; i++) {
    pool[i]->Trian_Vertex_show_coords();
  }
}

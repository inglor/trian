#include "Mesh.hh"

#include <cassert>
#include <iostream>
#include <random>

static float Random_Float_Between(float min, float max) {
  static std::random_device random;
  static std::default_random_engine random_engine(random());
  static std::uniform_real_distribution<> random_distribution(min, max);
  return random_distribution(random_engine);
}

Mesh::Mesh(FILE *input_file) {
  std::vector<Vertex>::size_type pool_size;
  fread(&pool_size, sizeof(std::vector<Vertex>::size_type), 1, input_file);
  std::cout << "Pool size read: " << pool_size << std::endl;
  pool.reserve(pool_size);

  float buffer[3 * 1024];
  float c = 0;
  int cp = pool_size;
  // int read=0;
  while (cp) {
    cp--;
    if (c == 0) {
      c = fread((void *)buffer, sizeof(float), 3 * 1024, input_file);
    }
    for (int i = 1; i < 3; i++) {
      std::cout << "v:" << buffer[i] << std::endl;
    }
    assert(0 == 1 && "NIKOS: this is definitelly wrong, FIX IT");
    pool[c] = Vertex(buffer[0], buffer[1], buffer[2]);
    c--;
  }
}

Mesh::Mesh(int size) {
  pool.reserve(size);
  Init_Random_Values(size);
}

// NIKOS TODO: copying to buffer and writing out is useless, replace with
// simpler IO or maybe with using directly the pool.data() buffer
void Mesh::SaveToFile(FILE *f) {
  float buffer[3 * 1024];

  fwrite(pool.data(), sizeof(std::vector<Vertex>::size_type), 1, f);
  int cp = pool.size();
  int c = 0;
  while (cp) {
    cp--;
    buffer[c] = pool[cp][0];
    c++;
    buffer[c] = pool[cp][1];
    c++;
    buffer[c] = pool[cp][2];
    c++;
    if (c == 3 * 1024 || cp == 0) {
      fwrite((void *)buffer, sizeof(float), c, f);
      c = 0;
    }
  }
}

void Mesh::Init_Random_Values(size_t N) {
  for (size_t i = 0; i < N; i++) {
    pool.emplace_back(Random_Float_Between(0.0, 10.0),
                      Random_Float_Between(0.0, 10.0),
                      Random_Float_Between(0.0, 10.0));
  }
}

void Mesh::PrintFirstN(size_t N) {
  std::cout << "Printing top " << N << " vertices\n";
  for (size_t i = 0; i < pool.size() && i < N; i++) {
    std::cout << "v[" << i << "] = " << pool[i] << "\n";
  }
}

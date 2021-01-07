#ifndef TRIAN_TRIAN_HH
#define TRIAN_TRIAN_HH

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Mesh.hh"

#define TRIAN_DEF_POOL_SIZE 1024
#define TRIAN_DATA_SET_FILE "coords.bin"

class Trian {
public:
  Trian();

  Trian(int argc, char **argv);

  virtual ~Trian();

  void Trian_Initiate();

private:
  void Trian_Arguments();

  void Trian_ShowArgs();

  int poolsize{};
  int Use_DataFile{};
  int Argc{};
  char **Argv{};
  const char *dataset{};
  FILE *dataset_file{};
  Mesh *aMesh{};
};

#endif //TRIAN_TRIAN_HH

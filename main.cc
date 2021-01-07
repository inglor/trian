#include <iostream>
#include <random>
#include "Trian.hh"

int main(int argc, char **argv) {
  // Seed with a real random value, if available
  random_device random;
  default_random_engine random_engine(random());
  uniform_real_distribution<> random_distribution(
      numeric_limits<float>::min(),
      numeric_limits<float>::max());
  std::cout << "Randomly-chosen mean: " << random_distribution(random_engine) << std::endl;
  auto *Triangle = new Trian(argc, argv);
  Triangle->Trian_Initiate();
//  Mesh *aMesh = new Mesh(1024, false);
//  fprintf(stdout, "New Mesh Created\nAs long as a [%d] vertex pool", 1024);

//  fprintf(stdout, "\nParta.... \n");
//  aMesh->Trian_Mesh_ShowPool();

//  FILE * _dataset;
//  _dataset = fopen ( "coords.bin" , "wb" );
//  if (_dataset)
//  {
//    aMesh->Trian_Mesh_Save_Dataset(_dataset);
//    fclose(_dataset);
//    fprintf(stdout, "File saved...\n");
//  }
//
//  delete aMesh;
//  fprintf(stdout, "\n");
  return 0;
}

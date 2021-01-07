#include <iostream>

#include "Trian.hh"

int main(int argc, char **argv) {
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

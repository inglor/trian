#include <cstring>
#include <iostream>
#include <memory>

#include "Graphics.hh"
#include "Mesh.hh"

static int poolsize = 1024;
static bool DataFileUse = false;
static const char *DataFileName = "coords.bin";

static void ArgsCLIShow(int argc, char **argv) {
  int temp_argc = argc;
  while (temp_argc-- > 0) {
    std::cout << "Arg[ " << temp_argc << " ] - [ " << argv[temp_argc] << " ]\n";
  }
}

static void ArgsCLIParse(int argc, char **argv) {
  int temp_argc = argc;
  while (temp_argc-- > 0) {
    if (strstr(argv[temp_argc], "--DataSet")) {
      DataFileName = strstr(argv[temp_argc], "=") + 1;
      DataFileUse = true;
    }
    if (strstr(argv[temp_argc], "--PoolSize")) {
      poolsize = std::stoi(strstr(argv[temp_argc], "=") + 1);
      DataFileUse = false;
    }
  }
}

int main(int argc, char **argv) {
  std::cout << "arguments given:\n";
  ArgsCLIShow(argc, argv);
  ArgsCLIParse(argc, argv);

  std::unique_ptr<Mesh>
      MyMesh;  // NIKOS: The Proper thing to use here is a factory and we
               // wouldn't use a pointer to a Mesh. L8r...
  if (DataFileUse) {
    std::cout << "Reading Mesh from datafile: " << std::string{DataFileName}
              << "\n";
    FILE *fp = fopen(DataFileName, "rb");
    if (!fp) {
      std::cerr << "Error opening input file: " << std::string{DataFileName}
                << "Exiting\n";
      exit(-1);
    }
    MyMesh = std::make_unique<Mesh>(fp);
    fclose(fp);
  } else {
    std::cout << "Creating Mesh of random points with pool size of " << poolsize
              << "\n";
    MyMesh = std::make_unique<Mesh>(poolsize);
  }
  MyMesh->PrintFirstN();

  Graphics visualize("../src/position.vert", "../src/red.frag");
  visualize.Background(0.0f, 0.0f, 0.4f);  // Dark blue background
  visualize.PointData(MyMesh->ByteSize(), MyMesh->RawData());
  visualize.loop(MyMesh->Size());

  return 0;
}

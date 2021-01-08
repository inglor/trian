#include "Trian.hh"

using namespace std;

Trian::Trian() = default;

Trian::Trian(int argc, char **argv) {
  poolsize = TRIAN_DEF_POOL_SIZE;
  dataset = TRIAN_DATA_SET_FILE;
  Argc = argc;
  Argv = argv;
}

void Trian::Trian_ShowArgs() {
  int temp_argc = Argc;
  while (temp_argc > 0) {
    temp_argc--;
    cout << "Arg[" << temp_argc << "]-\t[" << Argv[temp_argc] << "]" << endl;
  }
}

void Trian::Trian_Arguments() {
  int temp_argc = Argc;
  while (temp_argc > 0) {
    temp_argc--;
    if (strstr(Argv[temp_argc], "--DataSet")) {
      dataset = strstr(Argv[temp_argc], "=") + 1;
      Use_DataFile = 1;
      cout << "Using Datafile.." << endl;
    }
    if (strstr(Argv[temp_argc], "--PoolSize")) {
      poolsize = stoi(strstr(Argv[temp_argc], "=") + 1);
      Use_DataFile = 0;
      cout << "Creating random Mesh with pool size of " << poolsize << endl;
    }
  }
}

void Trian::Trian_Initiate() {
  cout << "Initiating creation of Mesh using:" << endl;
  Trian_ShowArgs();
  Trian_Arguments();
  if (Use_DataFile) {
    cout << "Mesh created reading file:" << dataset << endl;
    dataset_file = fopen(dataset, "rb");
    aMesh = new Mesh(dataset_file);
    fclose(dataset_file);
  } else {
    aMesh = new Mesh(poolsize, false);
    cout << "New Mesh created with " << poolsize << " random vertexes" << endl;
    dataset_file = fopen(dataset, "wb");
    aMesh->Trian_Mesh_Save_Dataset(dataset_file);
    fclose(dataset_file);
  }

  cout << "Printing 25 first vertexes" << endl;
  aMesh->Trian_Mesh_ShowPool();
}

Trian::~Trian() { delete aMesh; }

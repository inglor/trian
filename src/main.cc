#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstring>
#include <iostream>
#include <memory>

#include "Mesh.hh"
GLFWwindow *window;
#include <glm/glm.hpp>

using namespace glm;

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
  // Initialise GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE);  // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(1024, 768, "Tutorial 01", nullptr, nullptr);
  if (window == nullptr) {
    fprintf(stderr,
            "Failed to open GLFW window. If you have an Intel GPU, they are "
            "not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  do {
    // Clear the screen. It's not mentioned before Tutorial 02, but it can cause
    // flickering, so it's there nonetheless.
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw nothing, see you in tutorial 2 !

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  }  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  std::cout << "arguments given:\n";
  ArgsCLIShow(argc, argv);
  ArgsCLIParse(argc, argv);

  std::unique_ptr<Mesh> MyMesh;
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

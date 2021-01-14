#include "Graphics.hh"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
//#include <glm/glm.hpp>
// using namespace glm;

static GLFWwindow *window;

Graphics::Graphics() {
  // Initialise GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE);  // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(1024, 768, "Tutorial 01", nullptr, nullptr);
  if (window == nullptr) {
    std::cerr
        << "Failed to open GLFW window. If you have an Intel GPU, they are "
           "not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW\n";
    exit(EXIT_FAILURE);
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

Graphics::~Graphics() {
  // Close OpenGL window and terminate GLFW
  glfwTerminate();
}

void Graphics::Background(float r, float g, float b) {
  glClearColor(r, g, b, 0.0f);
}

void Graphics::PointData(const size_t ByteSize, const float *RawData) {
  // Create a vertex array object
  // Use a Vertex Array Object
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create a Vector Buffer Object that will store the vertices on video memory
  glGenBuffers(1, &vbo);

  // Allocate space and upload the data from CPU to GPU
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, ByteSize, RawData, GL_STATIC_DRAW);

  // Get the location of the attributes that enters in the vertex shader
  GLint position_attribute = glGetAttribLocation(shaders[0].id, "position");

  // Specify how the data for position can be accessed
  glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

  // Enable the attribute
  glEnableVertexAttribArray(position_attribute);

  glEnable(GL_PROGRAM_POINT_SIZE);
}

void Graphics::loop(size_t NumPoints) {
  do {
    // Clear the screen. It's not mentioned before Tutorial 02, but it can cause
    // flickering, so it's there nonetheless.
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, NumPoints);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  }  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);
}

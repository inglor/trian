// NIKOS: shamelessly adapted from solarian programmer github code
#include "Shader.hh"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>

GLuint Shader::ShadersLink(const char *path_vert_shader,
                           const char *path_frag_shader) {
  // Load and compile the vertex and fragment shaders
  GLuint vertexShader = ShaderCompile(path_vert_shader, GL_VERTEX_SHADER);
  GLuint fragmentShader = ShaderCompile(path_frag_shader, GL_FRAGMENT_SHADER);

  // Attach the above shader to a program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  // Flag the shaders for deletion
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Link and use the program
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  return shaderProgram;
}

void Shader::ShaderFileRead(const char *fname, std::vector<char> &buffer) {
  std::ifstream in;
  in.open(fname);

  if (in.is_open()) {
    // Get the number of bytes stored in this file
    in.seekg(0, std::ios::end);
    size_t length = (size_t)in.tellg();

    // Go to start of the file
    in.seekg(0, std::ios::beg);

    // Read the content of the file in a buffer
    buffer.resize(length + 1);
    in.read(&buffer[0], length);
    in.close();
    // Add a valid C - string end
    buffer[length] = '\0';
  } else {
    std::cerr << "Unable to open " << fname << " I'm out!" << std::endl;
    exit(-1);
  }
}

GLuint Shader::ShaderCompile(const char *fname, GLenum shaderType) {
  // Load a shader from an external file
  std::vector<char> buffer;
  ShaderFileRead(fname, buffer);
  const char *src = &buffer[0];

  // Compile the shader
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);
  // Check the result of the compilation
  GLint test;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
  if (!test) {
    std::cerr << "Shader compilation failed with this message:" << std::endl;
    std::vector<char> compilation_log(512);
    glGetShaderInfoLog(shader, compilation_log.size(), NULL,
                       &compilation_log[0]);
    std::cerr << &compilation_log[0] << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  return shader;
}

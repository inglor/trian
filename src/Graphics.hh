#pragma once
#include <vector>
#include "Shader.hh"

class Graphics {
 public:
  explicit Graphics(void);
  explicit Graphics(const char* VertPath, const char* FragPath) : Graphics() {
    shaders.push_back(Shader(VertPath, FragPath));
  }
  ~Graphics();
  void Background(float, float, float);
  void PointData(const size_t, const float*);
  void loop(size_t NumPoints);

 private:
  std::vector<Shader> shaders;
  GLuint vao;
  GLuint vbo;
};

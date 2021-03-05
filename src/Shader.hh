#ifndef TRIAN_SHADER_HH
#define TRIAN_SHADER_HH
#include <GL/glew.h>

#include <vector>

class Shader {
 public:
  Shader(const char *VertPath, const char *FragPath) {
    id = ShadersLink(VertPath, FragPath);
  }
  void Use() { glUseProgram(id); }
  GLuint id = 0;

 private:
  GLuint ShadersLink(const char *path_vert_shader,
                     const char *path_frag_shader);
  void ShaderFileRead(const char *fname, std::vector<char> &buffer);
  GLuint ShaderCompile(const char *fname, GLenum shaderType);
};

#endif

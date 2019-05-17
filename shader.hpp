#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL/gl.h>

class Shader{
protected:
  GLuint VAO;
public:
  GLuint ID;
  bool good;
  Shader(const char * vertexPath, const char * fragmentPath);
  ~Shader();
  void setup(GLuint &vbo);
  void bindVAO();
  void use();
  GLuint * getVAO();
};

#endif

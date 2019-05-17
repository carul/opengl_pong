#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "setup.hpp"
#include <GL/gl.h>
#include <vector>
#include <string>

class Object{
protected:
  GLuint EBO, type;
  std::vector<GLuint> indices;
  std::vector<Vertex> vertices;
public:
  static Object * find(std::string name);
  std::string name;
  virtual void update();
  Object(GLuint type);
  virtual ~Object() = default;
  unsigned int addVertex(float x, float y, float red, float green, float blue, float alpha);
  unsigned int addIndices(GLuint i1, GLuint i2, GLuint i3);
  Vertex * getVertex(unsigned int id);
  void removeVertex(unsigned int id);
  void move(float x, float y);
  void create(const std::vector<Vertex>&vertices);
  void indice(const std::vector<GLuint>&indices);
  void draw(GLuint &VBO);
  void setPosition(float x, float y);
};

extern std::vector<Object*> GAMEOBJECTS;

#endif

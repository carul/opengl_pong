#include "object.hpp"
#include <iostream>

Object::Object(GLuint type){
  glGenBuffers(1, &this->EBO);
  this->type = type;
}

void Object::update(){

}

Object * Object::find(std::string name){
  Object * obj = NULL;
  for(auto && objptr : GAMEOBJECTS){
    if(objptr->name == name){
      obj = objptr;
      break;
    }
  }
  return obj;
}

void Object::create(const std::vector<Vertex>&vertices){
  this->vertices.clear();
  this->vertices = vertices;
}

Vertex * Object::getVertex(unsigned int id){
  return &this->vertices.at(id);
}

void Object::removeVertex(unsigned int id){
  this->vertices.erase(this->vertices.begin() + id);
}

void Object::setPosition(float x, float y){
  float dx = this->vertices.at(0).position[0] - x;
  float dy = this->vertices.at(0).position[1] - y;
  this->move(-dx, -dy);
}
unsigned int Object::addVertex(float x, float y, float red = 1.0, float green = 1.0, float blue = 1.0, float alpha = 1.0){
  Vertex v;
  v.position[0] = x;
  v.position[1] = y;
  v.color[0] = red;
  v.color[1] = green;
  v.color[2] = blue;
  v.color[3] = alpha;
  this->vertices.push_back(v);
  return vertices.size()-1;
}

void Object::move(float x, float y){
  for(auto&& i : this->vertices){
    i.position[0] += x;
    i.position[1] += y;
  }
}

unsigned int Object::addIndices(GLuint i1, GLuint i2, GLuint i3){
  this->indices.push_back(i1);
  this->indices.push_back(i2);
  this->indices.push_back(i3);
  return this->indices.size()-1;
}

void Object::indice(const std::vector<GLuint>&indices){
  this->indices.clear();
  this->indices = indices;
}


void Object::draw(GLuint &VBO){
  GLint array;
  glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &array);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(Vertex), this->vertices.data(), this->type);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size()*sizeof(GLuint), this->indices.data(), this->type);
  glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ARRAY_BUFFER, array);
}

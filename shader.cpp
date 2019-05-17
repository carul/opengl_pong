#include "setup.hpp"
#include "shader.hpp"
#include <fstream>
#ifdef DEBUG
#include <iostream>
#endif

Shader::Shader(const char * vertexPath, const char * fragmentPath){
  this->ID = glCreateProgram();
  glGenVertexArrays(1, &(this->VAO));
  this->good = true;
  #ifdef DEBUG
    std::cout << "Shader initialising." << std::endl;
  #endif
  std::fstream vertexFile, fragmentFile;
  std::string vertexSource, fragmentSource, lineIn;
  vertexFile.open(vertexPath, std::ios_base::in);
  fragmentFile.open(fragmentPath, std::ios_base::in);
  if(!vertexFile.good()){
    #ifdef DEBUG
      std::cerr << "Error while opening vertex shader file" << std::endl;
    #endif
    this->good = false;
  }
  if(!fragmentFile.good()){
    #ifdef DEBUG
      std::cerr << "Error while opening fragment shader file" << std::endl;
    #endif
    this->good = false;
  }
  if(this->good){
    while(std::getline(vertexFile, lineIn)){
      vertexSource+=lineIn + '\n';
    }
    while(std::getline(fragmentFile, lineIn)){
      fragmentSource+=lineIn + '\n';
    }
    vertexFile.close();
    fragmentFile.close();

    GLuint vID, fID;
    vID=glCreateShader(GL_VERTEX_SHADER);
    fID=glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar * vertexPointer = vertexSource.c_str();
    const GLchar * fragmentPointer = fragmentSource.c_str();
    glShaderSource(vID, 1, &vertexPointer, NULL);
    glShaderSource(fID, 1, &fragmentPointer, NULL);

    glCompileShader(vID);
    glCompileShader(fID);

    char infoLog[512];
    int success;

    glGetShaderiv(vID, GL_COMPILE_STATUS, &success);
    if(!success){
      this->good = false;
      #ifdef DEBUG
        glGetShaderInfoLog(vID, 512, NULL, infoLog);
        std::cerr << "Error while compiling vertex shader: \n" << infoLog << std::endl;
      #endif
    }

    glGetShaderiv(fID, GL_COMPILE_STATUS, &success);
    if(!success){
      this->good = false;
      #ifdef DEBUG
        glGetShaderInfoLog(fID, 512, NULL, infoLog);
        std::cerr << "Error while compiling fragment shader: \n" << infoLog << std::endl;
      #endif
    }

    if(this->good){
      glAttachShader(this->ID, vID);
      glAttachShader(this->ID, fID);
      glLinkProgram(this->ID);
      glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
      if(!success){
        this->good = false;
        #ifdef DEBUG
          glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
          std::cerr << "Error while linking shader program: \n" << infoLog << std::endl;
        #endif
      }
    }

    glDeleteShader(vID);
    glDeleteShader(fID);
  }
}

void Shader::setup(GLuint &vbo){
  GLint tVAO;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &tVAO);
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));
  glEnableVertexAttribArray(1);
  glBindVertexArray(tVAO);
}

GLuint *  Shader::getVAO(){
  return &this->VAO;
}

void Shader::bindVAO(){
  glBindVertexArray(this->VAO);
}

void Shader::use(){
  glUseProgram(this->ID);
}

Shader::~Shader(){
  glDeleteProgram(this->ID);
  glDeleteVertexArrays(1, &this->VAO);
}

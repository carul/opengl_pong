#include "setup.hpp"
#include "defines.hpp"
#include "GameObjects/paddle.hpp"
#include "GameObjects/ball.hpp"
#include "GameObjects/icon.hpp"
#include <iostream>
#include <algorithm>
#include <GL/gl.h>
#include <string.h>

bool DOWN_PRESSED = false;
bool UP_PRESSED = false;
bool W_PRESSED = false;
bool S_PRESSED = false;

void loadObjects(){
  Object * border = new Object(GL_STATIC_DRAW);
  border->create(BORDER_DATA);
  border->indice(BORDER_INDICES);
  GAMEOBJECTS.push_back(border);

  Paddle * paddle = new Paddle(GL_DYNAMIC_DRAW);
  paddle->create(PADDLE1_DATA);
  paddle->indice(PADDLE1_INDICES);
  paddle->mode = Paddle::PLAYER1;
  paddle->name = "PADDLE1";
  GAMEOBJECTS.push_back(paddle);

  paddle = new Paddle(GL_DYNAMIC_DRAW);
  paddle->create(PADDLE2_DATA);
  paddle->indice(PADDLE2_INDICES);
  paddle->mode = Paddle::PLAYER2;
  paddle->name = "PADDLE2";
  GAMEOBJECTS.push_back(paddle);

  Ball * ball = new Ball(GL_DYNAMIC_DRAW);
  ball->create(BALL_DATA);
  ball->indice(BALL_INDICES);
  ball->name = "BALL";
  GAMEOBJECTS.push_back(ball);

  Icon * icon = new Icon(GL_DYNAMIC_DRAW);
  icon->create(PC_ICON_DATA);
  icon->indice(PC_ICON_INDICES);
  icon->name = "PC_ICON";
  icon->setPosition(-0.1f, -0.8f);
  GAMEOBJECTS.push_back(icon);

  icon = new Icon(GL_DYNAMIC_DRAW);
  icon->create(PAUSE_ICON_DATA);
  icon->indice(PAUSE_ICON_INDICES);
  icon->name = "PAUSE_ICON";
  icon->setPosition(0.1f, -0.8f);
  GAMEOBJECTS.push_back(icon);
}

void framebufferSizeCallback(GLFWwindow * window, int width, int height){
  glViewport(0, 0, width, height);
}

Vertex::Vertex(){
  std::fill(this->position, this->position+2, 0.0f);
  std::fill(this->color, this->color+4, 1.0f);
}

Vertex::Vertex(const std::vector<float>&data){
  if(data.size()==2){
    std::fill(this->color, this->color+4, 0.4f);
    this->position[0] = data.at(0);
    this->position[1] = data.at(1);
  }
  else if(data.size()==6){
    this->position[0] = data.at(0);
    this->position[1] = data.at(1);
    for(unsigned i = 0; i < 4; i++)
      this->color[i] = data.at(2+i);
  }
}

void parseInput(GLFWwindow * window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
    DOWN_PRESSED = true;
  }
  else{
    DOWN_PRESSED = false;
  }
  if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
    UP_PRESSED = true;
  }
  else{
    UP_PRESSED = false;
  }
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    S_PRESSED = true;
  }
  else{
    S_PRESSED = false;
  }
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    W_PRESSED = true;
  }
  else{
    W_PRESSED = false;
  }
  if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && buttonTimers.at(GLFW_KEY_C)<=0){
    buttonTimers.at(GLFW_KEY_C) = 0.4f;
    Icon * ic = (Icon*)Object::find("PC_ICON");
    if(ic){
      ic->activated ^= 1;
      if(ic->activated){
        ic->setColor(0.0f, 0.2f, 1.0f, 1.0f);
        ((Paddle*)Object::find("PADDLE2"))->mode=Paddle::PC;
      }
      else{
        ic->setColor(0.4f, 0.4f, 0.4f, 0.4f);
        ((Paddle*)Object::find("PADDLE2"))->mode=Paddle::PLAYER2;
      }
    }
  }
  if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && buttonTimers.at(GLFW_KEY_P) <= 0){
    buttonTimers.at(GLFW_KEY_P) = 0.4f;
    Icon * ic = (Icon*)Object::find("PAUSE_ICON");
    if(ic){
      GAME_PAUSED ^= 1;
      if(GAME_PAUSED)
        ic->setColor(0.0f, 0.2f, 1.0f, 1.0f);
      else
        ic->setColor(0.4f, 0.4f, 0.4f, 0.4f);
    }
  }
  if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
    scorep1 = scorep2 =0;
    for(unsigned i = 0; i !=GAMEOBJECTS.size();){
      if(GAMEOBJECTS.at(i)->name == "POINT"){
        i = std::distance(GAMEOBJECTS.begin(), GAMEOBJECTS.erase(GAMEOBJECTS.begin()+i));
      }
      else{
        if(GAMEOBJECTS.at(i)->name == "BALL"){
          ((Ball*)GAMEOBJECTS.at(i))->reset();
        }
        i++;
      }
    }
  }
}

GLFWwindow * setup(){
  #ifdef DEBUG
    std::cout << "Opengl pong initialising." << std::endl;
  #endif
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  GLFWwindow * window = glfwCreateWindow(800, 600, "Pong Opengl", NULL, NULL);
  if(window == NULL){
    #ifdef DEBUG
      std::cerr << "Error while creating a new opengl window" << std::endl;
    #endif
  }

  glfwMakeContextCurrent(window);
  glewExperimental = true;
  glewInit();

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glViewport(0, 0, 800, 600);
  glClearColor(0.0, 0.0, 0.0, 1.0f);

  memset(buttonTimers.data(), 0.0f, buttonTimers.size());

  return window;
}

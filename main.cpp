#include "defines.hpp"
#include "setup.hpp"
#include "shader.hpp"
#include "object.hpp"
#include <iostream>
#include <ctime>
#include <random>

std::vector<Object*> GAMEOBJECTS;
std::vector<float> buttonTimers(350);
double DELTATIME = 0;
bool GAME_PAUSED = false;
unsigned short scorep1 = 0;
unsigned short scorep2 = 0;

int main(){
  srand( time(NULL));
  GLFWwindow * window = setup();
  Shader windowShader("vertexshader.glsl", "fragmentshader.glsl");
  if(windowShader.good == false){
    std::cout << "Initialisation error." << std::endl;
    return -1;
  }
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  windowShader.setup(VBO);
  windowShader.bindVAO();
  windowShader.use();
  loadObjects();

  clock_t ticks = clock();
  while(!glfwWindowShouldClose(window)){
    DELTATIME = double(clock() - ticks)/CLOCKS_PER_SEC;
    for(auto && tim : buttonTimers){
      if(tim > 0){
        tim -= DELTATIME;
        if(tim <= 0)
          tim = 0;
      }
    }
    if(GAME_PAUSED)
      DELTATIME = 0;
    ticks = clock();
    parseInput(window);
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << GAMEOBJECTS.size() << std::endl;
    for(auto && obj : GAMEOBJECTS){
      obj->update();
      obj->draw(VBO);
    }
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  for(auto && obj : GAMEOBJECTS)
    delete obj;
  glfwTerminate();
  return 0;
}

#ifndef SETUP_HPP
#define SETUP_HPP
#include "defines.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

struct Vertex{
  float position[2];
  float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  Vertex();
  Vertex(const std::vector<float>&data);
};

void framebufferSizeCallback(GLFWwindow * window, int width, int height);

void parseInput(GLFWwindow * window);

void loadObjects();

GLFWwindow * setup();

#endif

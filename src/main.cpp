/*
  Arkanoid
  - platform moving left\right by keyboard
  - ball bounces out of sides, platform and top
  - bottom side is endgame
  - bricks generates randomly on the start
*/

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void glfw_error_callback(int error, const char* desc);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

int main(int argc, char** argv) {
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    std::cout << "glfw initialization failed." << '\n';
    return -1;
  }

  auto window = glfwCreateWindow(800, 600, "Arkanoid", NULL, NULL);
  if(!window) {
    std::cout << "glfw window initialization failed." << '\n';
    return -1;
  }
  if (!glewInit()) {
    std::cout << "glew initialization failed." << '\n';
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height); 
  glfwSwapInterval(1);

  while(!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);



      glfwSwapBuffers(window);
      glfwPollEvents();
  }


  glfwDestroyWindow(window);
  glfwTerminate();
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void glfw_error_callback(int error, const char* desc) {
  std::cout << "[GLFW] error #" << error << " " << desc << '\n';
}
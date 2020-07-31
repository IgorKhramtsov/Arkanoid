/*
  Arkanoid
  - platform moving left\right by keyboard
  - ball bounces out of sides, platform and top
  - bottom side is endgame
  - bricks generates randomly on the start
*/

#include <stdio.h>
#include <iostream>

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "GameObject.h"
#include "Shader.h"
#include "utils.h"

void glfw_error_callback(int error, const char* desc);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void gldebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

int main(int argc, char** argv) {
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
  glfwMakeContextCurrent(window);
  if (glewInit() != 0) {
    std::cout << "glew initialization failed." << '\n';
    return -1;
  }
  glfwSetKeyCallback(window, key_callback);
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height); 
  glfwSwapInterval(1);

  // auto brick = Brick();
  // brick.setPosition(100, 100);
  // brick.setColor(0.4f, 0.4f, 0.7f, 1.f);

  // ...

  // brick.Draw();

  Renderer renderer = Renderer((float)width, (float)height);
  GameObject bricks[30];
  auto brick = GameObject();
  int padding_x = 50, padding_y = 200;
  int spacing = 10;
  int brick_w = (width - padding_x * 2 - (spacing * 15)) / 15, brick_h = 20;
  auto renderable = renderer.CreateRect(brick_w, brick_h);

  for (int i = 0; i < 30; i++) {
    bricks[i] = GameObject();
    bricks[i].renderebale = renderable;
    bricks[i].setPosition(
      padding_x + (brick_w + spacing) * (i % 15),
      ((float)height - padding_y) - ((brick_h + spacing) * (i % 2))
      );
    bricks[i].setColor(0.3f, 0.3f, 0.7f, 1.f);
  }
  GameObject platform = GameObject();
  platform.renderebale = renderer.CreateRect(120, 20);
  platform.setColor(0.3f, 0.43f, 0.3f, 1.f);
  platform.setPosition(width / 2.f - 120.f / 2.f, 20.f + 30.f);

  GameObject ball = GameObject();
  ball.renderebale = renderer.CreateRect(25, 25);
  ball.setColor(0.7f, 0.3f, 0.3f, 1.f);
  ball.setPosition(platform.transform.pos.x + 120.f / 2.f - 25.f / 2.f, platform.transform.pos.y + 30.f);
  
  Shader SimpleShader = Shader("assets/brick.vert", "assets/brick.frag");
  Shader RoundShader = Shader("assets/brick.vert", "assets/ball.frag");

  float r = 0.3f, g = 0.3f, b = 0.3f;
  float r_v = 0.05f, g_v = 0.03f, b_v = 0.07f;
  while(!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

      for (int i = 0; i < 30; i++) {
        renderer.Draw(bricks[i], SimpleShader);
      }
      renderer.Draw(platform, SimpleShader);
      renderer.UseShader(RoundShader);
      RoundShader.setUniformVec2f("u_Center", ball.getCenter());
      RoundShader.setUniform1f("u_Radius", ball.renderebale.height / 2.);
      renderer.Draw(ball, RoundShader);

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


// void gldebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
//   std::cout << message << '\n';
//   __debugbreak();
// }
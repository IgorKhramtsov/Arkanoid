/*
  Arkanoid
  - platform moving left\right by keyboard
  - ball bounces out of sides, platform and top
  - bottom side is endgame
  - bricks generates randomly on the start
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "utils.h"

void glfw_error_callback(int error, const char* desc);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void gldebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);



unsigned int compileShader(unsigned int type, const char *src) {
  auto shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  int result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    auto message = new char[length];
    glGetShaderInfoLog(shader, length, &length, message);
    std::cout << "Failed to compile shader: " << message << '\n';
    delete message;
    return 0;
  }

  return shader;
}

unsigned int createShaderProgram(const char* vertexSource, const char* fragmentSource) {
  auto program = glCreateProgram();
  auto vs = compileShader(GL_VERTEX_SHADER, vertexSource);
  auto fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
  if (vs == 0 || fs == 0) return 0; // mb remove

  glAttachShader(program, vs);
  glAttachShader(program, fs);

  glLinkProgram(program);
  glValidateProgram(program);

  return program;
}

void loadShader(const char *filename, char** source) {
  std::cout << "Scanning file " << filename << '\n';

  std::ifstream file;
  file.open(filename, std::ios::binary);

  if (!file.is_open()) {
    std::cout << "Cant open file " << filename << '\n';
    exit(1);
  }

  file.seekg(0, std::ios::end);
  size_t length = file.tellg();
  file.seekg(0, std::ios::beg);

  auto buffer = new char[length + 1];
  file.read(buffer, length);
  file.close();
  buffer[length] = '\0';
  *source = buffer;
}

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

  Renderer renderer = Renderer();
  auto brick = renderer.CreateBrick();

  char* vert;
  loadShader("assets/brick.vert", &vert);
  char* frag;
  loadShader("assets/brick.frag", &frag);
  auto program = createShaderProgram(vert, frag);
  glUseProgram(program);

  while(!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);
      //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

      renderer.Draw(brick);

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
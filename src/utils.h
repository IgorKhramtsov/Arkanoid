#pragma once
#include <GL/glew.h>
#include <iostream>

static void GLErrorsClear() { while(glGetError() != GL_NO_ERROR); }
static bool GLErrorsPrint(const char* fname);

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) GLErrorsClear();\
  x;\
  ASSERT(GLErrorsPrint(#x))

static bool GLErrorsPrint(const char* fname) {
  while(auto error = glGetError()) {
    std::cout << "[GL_Error] (0x0" << std::hex << error << ") " << "from " << fname << '\n';
    return false;
  }
  return true;
}

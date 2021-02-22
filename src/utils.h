#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>

#ifdef _MSC_VER
#define DEBUG_BREAK __debugbreak()
#else
#include <signal.h>
#define DEBUG_BREAK raise(SIGTRAP)
#endif

static void GLErrorsClear() { while(glGetError() != GL_NO_ERROR); }
static bool GLErrorsPrint(const char* fname);

#define ASSERT(x) if(!(x)) DEBUG_BREAK;
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

static int sign(float f) { 
  if (f > 0.) return 1.f;
  else if (f < 0.) return -1.f;
  else return 0.f;
}
#define MAX(x, y) (x >= y ? x : y)
#define MIN(x, y) (x <= y ? x : y)


static void readFile(const char *filename, char** source) {
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

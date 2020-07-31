#include "Shader.h"
#include "utils.h"
#include "FileWatcher.h"

#include <GL/glew.h>

Shader::Shader(const char* vert_file, const char* frag_file, bool hot) {
    char* vert;
    char* frag;
    if (hot) {
      FileWatcher watcher_vert = FileWatcher(vert_file, 350);
      watcher_vert.start([&vert_file, &vert]() -> void { readFile(vert_file, &vert); });

      FileWatcher watcher_frag(frag_file, 350);
      watcher_frag.start([&frag_file, &frag]() -> void { readFile(frag_file, &frag); });
    } else {
      readFile(vert_file, &vert);
      readFile(frag_file, &frag);
    }
    this->m_ProgramID = Shader::createShaderProgram(vert, frag);
}

Shader::~Shader() {
  glDeleteProgram(m_ProgramID);
}

unsigned int Shader::createShaderProgram(const char* vertexSource, const char* fragmentSource) {
  auto program = glCreateProgram();
  auto vs = Shader::compileShader(GL_VERTEX_SHADER, vertexSource);
  auto fs = Shader::compileShader(GL_FRAGMENT_SHADER, fragmentSource);
  if (vs == 0 || fs == 0) return 0; // mb remove

  glAttachShader(program, vs);
  glAttachShader(program, fs);

  glLinkProgram(program);
  glValidateProgram(program);

  return program;
}

unsigned int Shader::compileShader(unsigned int type, const char *src) {
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

void Shader::setUniform4f(const char* name, float v0, float v1, float v2, float v3) const {
  glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniformMat4f(const char* name, const glm::mat4 matrix) const {
  glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniformVec2f(const char* name, glm::vec2 vec) const {
  glUniform2fv(getUniformLocation(name), 1, &vec[0]);
}

void Shader::setUniform1f(const char* name, float v0) const {
  glUniform1f(getUniformLocation(name), v0);
}

int Shader::getUniformLocation(const char* name) const{
  auto location = glGetUniformLocation(m_ProgramID, name);
  if (location == -1) 
    std::cout << "Unifrom '" << name << "' doesnt exist" << '\n';
  
  return location;
}

void Shader::Bind() const {
   GLCALL(glUseProgram(m_ProgramID));
};
void Shader::UnBind() const {
   glUseProgram(0); 
};
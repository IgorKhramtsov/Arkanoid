#pragma once

#include <glm/glm.hpp>

class Shader {
private:
    unsigned int m_ProgramID;

    static unsigned int createShaderProgram(const char* vertexSource, const char* fragmentSource);
    static unsigned int compileShader(unsigned int type, const char *src);

public:

    Shader(const char*, const char*, bool = false);
    ~Shader();

    void setUniform4f(const char* name, float v0, float v1, float v2, float v3) const;
    void setUniformMat4f(const char* name, const glm::mat4 matrix) const;
    void setUniformVec2f(const char* name, glm::vec2 vec) const;
    void setUniform1f(const char* name, float v0) const;
    int getUniformLocation(const char* name) const;

    void Bind() const;
    void UnBind() const;
    unsigned int getProgramID() const { return this->m_ProgramID; };
};
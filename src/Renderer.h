#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

class GameObject;

struct Transform {
    glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);
    glm::mat4 model = glm::mat4(1.0f);

    Transform() = default;
};

struct Renderable {
    unsigned int vao;
    float width;
    float height;
};

class Renderer {
private:
    glm::mat4 m_Proj;
    glm::mat4 m_View;

    unsigned int currentShader = 0;

    
public:
    Renderer(float width, float height);
    ~Renderer() = default;
    Renderable CreateRect(float w, float h);

    void UseShader(const Shader&);
    void Draw(const GameObject&, const Shader&);
};

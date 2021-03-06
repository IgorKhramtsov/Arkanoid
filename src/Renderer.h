#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

class GameObject;

struct Transform {
    glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 velocity = glm::vec3(0.f, 0.f, 0.f);
    glm::vec2 size;

    Transform() = default;
};

struct Renderable {
    unsigned int vao;
    float width;
    float height;
    const Shader *shader;
};

class Renderer {
private:
    glm::mat4 m_Proj;
    glm::mat4 m_View;
    glm::vec4 m_ClearColor;

    unsigned int currentShader = 0;

    
public:
    Renderer() = default;
    Renderer(float width, float height);
    ~Renderer() = default;
    Renderable CreateRect(float w, float h, const Shader &s);

    void setClearColor(float v0, float v1, float v2, float v3);
    void Clear();

    void UseShader(const Shader&);
    void UseShader(const Shader *);
    void Draw(const GameObject&, const Shader&);
    void Draw(const GameObject *,const Shader *);
};

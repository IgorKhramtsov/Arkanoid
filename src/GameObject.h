#pragma once

#include "Renderer.h"

class GameObject {
public:
    Renderable renderebale;
    Transform transform;
    glm::vec4 color = glm::vec4(1.f, 0.f, 0.f, 1.f);
    
    GameObject() = default;
    GameObject(Renderable r, Transform t, glm::vec4 c);

    glm::vec2 getCenter() const;
    void setColor(float v0, float v1, float v2, float v3);
    void setPosition(float x, float y);
    void setScale(float x, float y);
};
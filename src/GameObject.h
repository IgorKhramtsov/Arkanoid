#pragma once

#include "Renderer.h"

class GameObject {
    Renderable m_Renderebale;
    bool m_Dead = false;
    float m_Radius; // Destroy effect
    float m_RadiusShrink = 2.f; // Destroy effect

public:
    Transform transform;
    glm::vec4 color = glm::vec4(1.f, 0.f, 0.f, 1.f);
    
    GameObject() = default;

    glm::vec2 getCenter() const;
    void setRenderable(Renderable);
    Renderable const &getRenderable() const;
    void setColor(float v0, float v1, float v2, float v3);
    void setPosition(float x, float y);
    void move(float x, float y);
    void setScale(float x, float y);
    void Destroy();
    bool isDead() const;
    float getDestroyEffRadius();
};
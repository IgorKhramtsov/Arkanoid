#pragma once

#include "Renderer.h"
#include "MyApp.h"

class MyApp;

class GameObject {
    Renderable m_Renderebale;
    bool m_Dead = false;
 
public:
    Transform transform;
    glm::vec4 color = glm::vec4(1.f, 0.f, 0.f, 1.f);
    
    GameObject() = default;
    virtual void OnUpdate(MyApp &) = 0;

    GameObject* setPosition(float x, float y);
    GameObject* setRenderable(Renderable);
    GameObject* setColor(float v0, float v1, float v2, float v3);
    glm::vec2 getCenter() const;
    
    Renderable const &getRenderable() const;
    
    void move(float x, float y);

    void Destroy();
    bool isDead() const;
};
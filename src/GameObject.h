#pragma once

#include "Renderer.h"

class MyApp;

class GameObject {
    Renderable m_Renderebale;
    bool m_Dead = false;
 
 protected:
    MyApp *app;
    Renderer *renderer;

public:
    Transform transform;
    glm::vec4 color = glm::vec4(1.f, 0.f, 0.f, 1.f);
    
    GameObject(MyApp *a, Renderable r);
    virtual void OnUpdate() = 0;
    virtual void OnDraw() = 0;

    GameObject& setPosition(float x, float y);
    GameObject& setColor(float v0, float v1, float v2, float v3);
    glm::vec2 getCenter() const;
    
    Renderable const &getRenderable() const;
    
    void move(float x, float y);

    void Destroy();
    bool isDead() const;
};
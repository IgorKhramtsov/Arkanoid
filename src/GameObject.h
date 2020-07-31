#pragma once

#include "Renderer.h"

class GameObject {
public:
    Renderable renderebale;
    Transform transform;
    glm::vec4 color = glm::vec4(1.f, 0.f, 0.f, 1.f);
    
    GameObject() = default;
    GameObject(Renderable r, Transform t, glm::vec4 c) : transform(t), color(c) 
    {
        this->renderebale = r;
    }

    glm::vec2 getCenter() const {
        return glm::vec2(transform.pos.x + renderebale.width / 2., transform.pos.y + renderebale.height / 2.);
    }

    void setColor(float v0, float v1, float v2, float v3) {
        color = glm::vec4(v0, v1, v2, v3);
    }

    void setPosition(float x, float y) {
        transform.pos[0] = x;
        transform.pos[1] = y;
    }

    void setScale(float x, float y) {
        transform.scale[0] = x;
        transform.scale[1] = y;
    }
};
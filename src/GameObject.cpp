#include "GameObject.h"
#include "utils.h"

glm::vec2 GameObject::getCenter() const {
    return glm::vec2(transform.pos.x + m_Renderebale.width / 2., transform.pos.y + m_Renderebale.height / 2.);
}

GameObject* GameObject::setRenderable(Renderable r) {
    m_Renderebale = r;
    transform.size = glm::vec2(r.width, r.height);
    return this;
}

Renderable const &GameObject::getRenderable() const {
    return m_Renderebale;
}

GameObject* GameObject::setColor(float v0, float v1, float v2, float v3) {
    color = glm::vec4(v0, v1, v2, v3);
    return this;
}

GameObject* GameObject::setPosition(float x, float y) {
    transform.pos[0] = x;
    transform.pos[1] = y;
    return this;
}

void GameObject::move(float x, float y) {
    transform.pos[0] += x;
    transform.pos[1] += y;
}

void GameObject::Destroy() {
    m_Dead = true;
}

bool GameObject::isDead() const {
    return m_Dead;
}


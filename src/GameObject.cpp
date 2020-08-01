#include "GameObject.h"
#include "utils.h"

glm::vec2 GameObject::getCenter() const {
    return glm::vec2(transform.pos.x + m_Renderebale.width / 2., transform.pos.y + m_Renderebale.height / 2.);
}

void GameObject::setRenderable(Renderable r) {
    m_Renderebale = r;
    transform.size = glm::vec2(r.width, r.height);
    m_Radius = MAX(r.width, r.height);
}

Renderable const &GameObject::getRenderable() const {
    return m_Renderebale;
}

void GameObject::setColor(float v0, float v1, float v2, float v3) {
    color = glm::vec4(v0, v1, v2, v3);
}

void GameObject::setPosition(float x, float y) {
    transform.pos[0] = x;
    transform.pos[1] = y;
}

void GameObject::move(float x, float y) {
    transform.pos[0] += x;
    transform.pos[1] += y;
}

void GameObject::setScale(float x, float y) {
    transform.scale[0] = x;
    transform.scale[1] = y;
}

void GameObject::Destroy() {
    m_Dead = true;
}

bool GameObject::isDead() const {
    return m_Dead;
}

float GameObject::getDestroyEffRadius() {
    m_Radius = MAX(0, (m_Radius - m_RadiusShrink));
    return m_Radius;
}
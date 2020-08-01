#include "GameObject.h"

GameObject::GameObject(Renderable r, Transform t, glm::vec4 c) : transform(t), color(c) 
{
    this->renderebale = r;
}

glm::vec2 GameObject::getCenter() const {
    return glm::vec2(transform.pos.x + renderebale.width / 2., transform.pos.y + renderebale.height / 2.);
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
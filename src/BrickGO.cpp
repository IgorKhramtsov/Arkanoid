#include "BrickGO.h"
#include "utils.h"

GameObject* BrickGO::setRenderable(Renderable r) {
    m_Radius = MAX(r.width, r.height);
    return GameObject::setRenderable(r);
}

float BrickGO::getDestroyEffRadius() {
    
    m_Radius = MAX(0, (m_Radius - m_RadiusShrink));
    return m_Radius;
}
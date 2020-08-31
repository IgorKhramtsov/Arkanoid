#include "BrickGO.h"
#include "utils.h"

BrickGO::BrickGO(MyApp *app, Renderable r) : GameObject(app, r) {
    m_Radius = MAX(r.width, r.height);
}

void BrickGO::OnUpdate() {
    if (blinkingColor >= 0.9f || blinkingColor <= 0.6f) 
        colorRate *= -1;
    blinkingColor += colorRate * (std::rand() % 10);
    blinkingColor = MIN(MAX(blinkingColor, 0.6f), 0.9f);

    if(isDead() && m_Radius > 0) {
        m_Radius = getDestroyEffRadius();
    }
}

void BrickGO::OnDraw()
{
    if(isDead()) {
        renderer->UseShader(getRenderable().shader);
        getRenderable().shader->setUniformVec2f("u_Center", getCenter());
        getRenderable().shader->setUniform1f("u_Radius", m_Radius);
        setColor(color.r + 0.1f, color.g, color.b, color.a);
    } else {
        renderer->UseShader(getRenderable().shader);
        getRenderable().shader->setUniform1f("u_Radius", -1.f);
        setColor(color.r, color.g, blinkingColor, color.a);
    }
    renderer->Draw(this, getRenderable().shader);
}

float BrickGO::getDestroyEffRadius() {
    m_Radius = MAX(0, (m_Radius - m_RadiusShrink));
    return m_Radius;
}
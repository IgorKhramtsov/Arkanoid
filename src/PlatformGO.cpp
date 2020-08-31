#include "PlatformGO.h"
#include "utils.h"

PlatformGO::PlatformGO(MyApp *app, Renderable r) : GameObject(app, r) {
    Application::getApp().getWindowSize(m_WindowWidth, m_WindowHeight);
}

void PlatformGO::OnUpdate() {
    // Platform movement
    auto pltSpeed = transform.velocity.x;
    if (Application::isKeyPressed(GLFW_KEY_LEFT) || Application::isKeyPressed(GLFW_KEY_RIGHT)) {
        curAccelerationSpeed += accelerationSpeed * (MAX(abs(curAccelerationSpeed), topAccelerationSpeed * 0.15f));
    } else {
        curAccelerationSpeed -= MIN(friction / 2., abs(curAccelerationSpeed)) * sign(curAccelerationSpeed);
        if (abs(pltSpeed) > 0)
            pltSpeed += MIN(friction * (MAX(abs(pltSpeed), 0.25f) / topSpeed), abs(pltSpeed)) * -sign(pltSpeed);
    }
    pltSpeed += curAccelerationSpeed * (Application::isKeyPressed(GLFW_KEY_LEFT) ? -1 : 1);
    curAccelerationSpeed = MIN(abs(curAccelerationSpeed), topAccelerationSpeed) * sign(curAccelerationSpeed);
    pltSpeed = MIN(abs(pltSpeed), topSpeed) * sign(pltSpeed);
    
    move(pltSpeed, 0.f);
    transform.velocity.x = pltSpeed;

    // Sides block
    if (transform.pos.x < 0) {
        transform.pos.x = 0;
        transform.velocity.x = 0;
        curAccelerationSpeed = 0;
    } else if (transform.pos.x > m_WindowWidth - transform.size.x) {
        transform.pos.x = m_WindowWidth - transform.size.x;
        transform.velocity.x = 0;
        curAccelerationSpeed = 0;
    }
}

void PlatformGO::OnDraw() 
{
    renderer->Draw(this, getRenderable().shader);
}
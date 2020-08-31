#include "BallGO.h"
#include "PlatformGO.h"

void BallGO::OnUpdate(MyApp &app) {
    // Ball movement
    if (app.getState() == State::START) {
        const auto center = app.getPlatform()->getCenter();
        setPosition(center.x - (25.f / 2.f), center.y + 30.f);
    } else {
        const auto ballNextPos = glm::vec3(getCenter(), .1f) + transform.velocity;
        const auto radius = transform.size.y / 2.;
        transform.velocity *= app.bounceVector(ballNextPos, radius);
        if ((ballNextPos.y - radius) < 0) {
            app.Start();
            return;
        }
        move(transform.velocity.x, transform.velocity.y);
    }
}
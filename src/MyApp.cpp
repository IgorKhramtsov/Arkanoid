#include "MyApp.h"
#include "utils.h"

MyApp::MyApp(const char *title, int width, int height) : Application(title, width, height) {
    m_Renderer.setClearColor(0.1f, 0.1f, 0.1f, 1.f);

    Start();
}

void MyApp::Start() {
    int width, height;
    getSize(width, height);
    
    int brick_w = ((width - padding_x * 2) - (spacing * 15)) / 15;
    int brick_h = 20;
    auto renderable = m_Renderer.CreateRect(brick_w, brick_h);

    for (int i = 0; i < 30; i++) {
        m_Bricks[i] = GameObject();
        m_Bricks[i].renderebale = renderable;
        m_Bricks[i].setPosition(
            padding_x + (brick_w + spacing) * (i % 15),
            ((float)height - padding_y) - ((brick_h + spacing) * (i % 2))
        );
        m_Bricks[i].setColor(0.3f, 0.3f, 0.7f, 1.f);
    }
    m_Platform = GameObject();
    m_Platform.renderebale = m_Renderer.CreateRect(120, 20);
    m_Platform.setColor(0.3f, 0.43f, 0.3f, 1.f);
    m_Platform.setPosition(width / 2.f - 120.f / 2.f, 20.f + 30.f);

    m_Ball = GameObject();
    m_Ball.renderebale = m_Renderer.CreateRect(25, 25);
    m_Ball.setColor(0.7f, 0.3f, 0.3f, 1.f);
    m_Ball.setPosition(m_Platform.transform.pos.x + 120.f / 2.f - 25.f / 2.f, m_Platform.transform.pos.y + 30.f);

    m_State = STATE_START;
}

void MyApp::onUpdate() {
    // TODO: Movement should be rewrited
    auto ballSpeed = m_Platform.transform.velocity.x;
    if (isKeyPressed(GLFW_KEY_LEFT)) {
        curAccelerationSpeed -= accelerationSpeed * (MAX(abs(curAccelerationSpeed), 0.25f) / topAccelerationSpeed);
    } else if (isKeyPressed(GLFW_KEY_RIGHT)) {
        curAccelerationSpeed += accelerationSpeed * (MAX(abs(curAccelerationSpeed), 0.25f) / topAccelerationSpeed);
    } else {
        curAccelerationSpeed -= MIN(friction / 2., abs(curAccelerationSpeed)) * sign(curAccelerationSpeed);
        if (abs(ballSpeed) > 0)
            ballSpeed += MIN(friction * (MAX(abs(ballSpeed), 0.25f) / topSpeed), abs(ballSpeed)) * -sign(ballSpeed);
    }
    ballSpeed += curAccelerationSpeed;
    curAccelerationSpeed = MIN(abs(curAccelerationSpeed), topAccelerationSpeed) * sign(curAccelerationSpeed);
    ballSpeed = MIN(abs(ballSpeed), topSpeed) * sign(ballSpeed);
    
    m_Platform.move(ballSpeed, 0.f);
    m_Platform.transform.velocity.x = ballSpeed;

    if (m_State == STATE_START) {
        auto center = m_Platform.getCenter();
        m_Ball.setPosition(center.x - (25.f / 2.f), center.y + 30.f);
    } else {
        m_Ball.move(m_Ball.transform.velocity.x, m_Ball.transform.velocity.y);
    }

    std::cout << "curAcc: " << curAccelerationSpeed << " curSpeed: " << ballSpeed << '\n';
}

void MyApp::onDraw() {
    for (int i = 0; i < 30; i++) {
        m_Renderer.Draw(m_Bricks[i], m_SimpleShader);
    }

    m_Renderer.Draw(m_Platform, m_SimpleShader);

    m_Renderer.UseShader(m_BallShader);
    m_BallShader.setUniformVec2f("u_Center", m_Ball.getCenter());
    m_BallShader.setUniform1f("u_Radius", m_Ball.renderebale.height / 2.);
    m_Renderer.Draw(m_Ball, m_BallShader);
}

void MyApp::onKeyCallback(int key, int action) {
    if (m_State == STATE_START && key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        m_Ball.transform.velocity.x = m_Platform.transform.velocity.x;
        m_Ball.transform.velocity.y = 6.f;
        m_State = STATE_GAME;
    }
}
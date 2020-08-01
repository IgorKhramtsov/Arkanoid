#include "MyApp.h"

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
}

void MyApp::onUpdate() {
    if (isKeyPressed(GLFW_KEY_LEFT))
        m_Platform.setPosition(m_Platform.transform.pos.x - 1.f, m_Platform.transform.pos.y);
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

}
#include "MyApp.h"
#include "utils.h"
#include "PlatformGO.h"
#include "BallGO.h"
#include "BrickGO.h"

MyApp::MyApp(const char *title, int width, int height) : Application(title, width, height) {
    m_Renderer.setClearColor(0.1f, 0.1f, 0.1f, 1.f);

    Start();
}

void MyApp::Start() {
    const int lines = 3;
    const int perLine = 14;
    const float brick_w = ((m_Width - padding_x * 2) - (spacing * perLine)) / perLine;
    const float brick_h = 20.f;
    const int m_BricksNumber = perLine * lines;
    const auto renderable = m_Renderer.CreateRect(brick_w, brick_h, m_RoundShader);
    gameObjects.clear();
    gameObjects.reserve(m_BricksNumber + 2);

    std::shared_ptr<BrickGO> brick;
    for (int k = 0; k < lines; ++k) {
        for (int i = 0; i < perLine; ++i) {
            brick = std::make_shared<BrickGO>(this, renderable);
            (*brick.get()).setColor(0.3f, 0.3f, 0.7f, 1.f)
                .setPosition(
                    padding_x + (brick_w + spacing) * (i),
                    ((float)m_Height - padding_y) - ((brick_h + spacing) * (k))
                );
            gameObjects.push_back(std::move(brick));
        }
    }

    srand((unsigned int)glfwGetTime());
    for (int k = 0; k < lines; ++k) {
        for (int i = 0; i < perLine / 2; ++i) {
            if (std::rand() % 4 == 0) {
                if (auto obj = dynamic_cast<BrickGO*>(gameObjects.at((k * perLine) + i).get())) 
                    obj->Destroy();
                if (auto obj = dynamic_cast<BrickGO*>(gameObjects.at((k * perLine) + (perLine - i - 1)).get()))
                    obj->Destroy();
            }
        }
    }
    m_Platform = std::make_shared<PlatformGO>(this, m_Renderer.CreateRect(120, 20, m_SimpleShader));
    (*m_Platform.get()).setColor(0.22f, 0.45f, 0.22f, 1.f)
        .setPosition(m_Width / 2.f - 120.f / 2.f + 16.f, 20.f + 30.f);
    gameObjects.push_back(m_Platform);

    m_Ball = std::make_shared<BallGO>(this, m_Renderer.CreateRect(25, 25, m_RoundShader));
    (*m_Ball.get()).setColor(0.9f, 0.35f, 0.35f, 1.f)
        .setPosition(m_Platform->transform.pos.x + 120.f / 2.f - 25.f / 2.f, m_Platform->transform.pos.y + 30.f);
    gameObjects.push_back(m_Ball);
    
    m_State = State::START;
}

void MyApp::onUpdate() {
    for (auto obj : gameObjects) {
        obj->OnUpdate();
    }
}

void MyApp::onDraw() {
    for (auto &object : gameObjects) {
        object->OnDraw();
    }
}

glm::vec3 MyApp::bounceVector(const glm::vec3 ballPos, const float radius) const {
    glm::vec3 bVec(1.f, 1.f, 1.f); // bounce vector
    if ((ballPos.x + radius) > m_Width || (ballPos.x - radius) < 0)
        bVec.x = -1;
    if ((ballPos.y + radius) > m_Height)
        bVec.y = -1;
    
    const auto r_diag = radius * 0.75; // distance to pi/4
    const auto ballT = glm::vec3(ballPos.x, ballPos.y + radius, 0.f);
    const auto ballB = glm::vec3(ballPos.x, ballPos.y - radius, 0.f);
    const auto ballL = glm::vec3(ballPos.x + radius, ballPos.y, 0.f);
    const auto ballR = glm::vec3(ballPos.x - radius, ballPos.y, 0.f);
    const auto ballLT = glm::vec3(ballPos.x + r_diag, ballPos.y + r_diag, 0.f);
    const auto ballRT = glm::vec3(ballPos.x - r_diag, ballPos.y + r_diag, 0.f);
    const auto ballLB = glm::vec3(ballPos.x + r_diag, ballPos.y - r_diag, 0.f);
    const auto ballRB = glm::vec3(ballPos.x - r_diag, ballPos.y - r_diag, 0.f);
    for ( auto &object : gameObjects) {
        if (dynamic_cast<BrickGO*>(object.get()) == nullptr || object->isDead())
            continue;
        if (isInside(ballT, object->transform) || isInside(ballB, object->transform) ||
            isInside(ballL, object->transform) || isInside(ballR, object->transform) ) {
                if ( abs(ballPos.x - object->getCenter().x) / object->transform.size.x >
                     abs(ballPos.y - object->getCenter().y) / object->transform.size.y)
                    bVec.x = -1;
                else
                    bVec.y = -1;

                object->Destroy();
                // return bVec;
            }
        else if (isInside(ballLT, object->transform) || isInside(ballRT, object->transform) || 
            isInside(ballLB, object->transform) || isInside(ballRB, object->transform)) {
                bVec.x = -1;
                bVec.y = -1;
                object->Destroy();
            }
    }

    // Platform collision - move to bricks collision
    if (isInside(ballT, m_Platform->transform) || isInside(ballB, m_Platform->transform) ||
        isInside(ballL, m_Platform->transform) || isInside(ballR, m_Platform->transform) ) {
        if ( abs(ballPos.x - m_Platform->getCenter().x) / m_Platform->transform.size.x >
                abs(ballPos.y - m_Platform->getCenter().y) / m_Platform->transform.size.y)
            bVec.x = -1;
        else
            bVec.y = -1;
        m_Ball->transform.velocity.x = MIN(10.f, abs(m_Platform->transform.velocity.x)) * sign(m_Platform->transform.velocity.x);
    }

    return bVec;
}

bool MyApp::isInside(glm::vec3 point, Transform target) const {
    return (point.x >= target.pos.x && point.x <= target.pos.x + target.size.x) &&
            (point.y >= target.pos.y && point.y <= target.pos.y + target.size.y);
}

void MyApp::onKeyCallback(int key, int action) 
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        CloseWindow();
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (m_State == State::START) {
            m_Ball->transform.velocity.x = MIN(10.f, abs(m_Platform->transform.velocity.x)) * sign(m_Platform->transform.velocity.x);
            m_Ball->transform.velocity.y = 6.f;
            m_State = State::GAME;
        } else {
            Start();
        }
    }
}

State MyApp::getState() const
{
    return m_State;
}

const std::shared_ptr<PlatformGO> MyApp::getPlatform() const
{
    return m_Platform;
}
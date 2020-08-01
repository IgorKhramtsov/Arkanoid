#include "MyApp.h"
#include "utils.h"

float MyApp::colorRate = 0.005f;
float MyApp::blinkingColor = 0.8f;
MyApp::MyApp(const char *title, int width, int height) : Application(title, width, height) {
    m_Renderer.setClearColor(0.1f, 0.1f, 0.1f, 1.f);

    Start();
}

void MyApp::Start() {
    const int lines = 3;
    const int perLine = 14;
    m_BricksNumber = perLine * lines;
    const int brick_w = ((m_Width - padding_x * 2) - (spacing * perLine)) / perLine;
    const int brick_h = 20;
    const auto renderable = m_Renderer.CreateRect(brick_w, brick_h);
    delete m_Bricks;
    m_Bricks = new GameObject[m_BricksNumber];

    
    for (int k = 0; k < lines; ++k) {
        for (int i = 0; i < perLine; ++i) {
            m_Bricks[i + (k * perLine)] = GameObject();
            m_Bricks[i + (k * perLine)].setRenderable(renderable);
            m_Bricks[i + (k * perLine)].setPosition(
                padding_x + (brick_w + spacing) * (i),
                ((float)m_Height - padding_y) - ((brick_h + spacing) * (k))
            );
            m_Bricks[i + (k * perLine)].setColor(0.3f, 0.3f, 0.7f, 1.f);
        }
    }

    srand((unsigned int)glfwGetTime());
    for (int k = 0; k < lines; ++k) {
        for (int i = 0; i < perLine / 2; ++i) {
            if (std::rand() % 4 == 0) {
                m_Bricks[(k * perLine) + i].Destroy();
                m_Bricks[(k * perLine) + (perLine - i - 1)].Destroy();
            }
        }
    }

    m_Platform = GameObject();
    m_Platform.setRenderable(m_Renderer.CreateRect(120, 20));
    m_Platform.setColor(0.22f, 0.45f, 0.22f, 1.f);
    m_Platform.setPosition(m_Width / 2.f - 120.f / 2.f    + 16.f, 20.f + 30.f);

    m_Ball = GameObject();
    m_Ball.setRenderable(m_Renderer.CreateRect(25, 25));
    m_Ball.setColor(0.9f, 0.35f, 0.35f, 1.f);
    m_Ball.setPosition(m_Platform.transform.pos.x + 120.f / 2.f - 25.f / 2.f, m_Platform.transform.pos.y + 30.f);

    m_State = STATE_START;
}

void MyApp::onUpdate() {
    // Platform movement
    auto ballSpeed = m_Platform.transform.velocity.x;
    if (isKeyPressed(GLFW_KEY_LEFT) || isKeyPressed(GLFW_KEY_RIGHT)) {
        curAccelerationSpeed += accelerationSpeed * (MAX(abs(curAccelerationSpeed), topAccelerationSpeed * 0.15f));
    } else {
        curAccelerationSpeed -= MIN(friction / 2., abs(curAccelerationSpeed)) * sign(curAccelerationSpeed);
        if (abs(ballSpeed) > 0)
            ballSpeed += MIN(friction * (MAX(abs(ballSpeed), 0.25f) / topSpeed), abs(ballSpeed)) * -sign(ballSpeed);
    }
    ballSpeed += curAccelerationSpeed * (isKeyPressed(GLFW_KEY_LEFT) ? -1 : 1);
    curAccelerationSpeed = MIN(abs(curAccelerationSpeed), topAccelerationSpeed) * sign(curAccelerationSpeed);
    ballSpeed = MIN(abs(ballSpeed), topSpeed) * sign(ballSpeed);
    
    m_Platform.move(ballSpeed, 0.f);
    m_Platform.transform.velocity.x = ballSpeed;

    // Sides block
    if (m_Platform.transform.pos.x < 0) {
        m_Platform.transform.pos.x = 0;
        m_Platform.transform.velocity.x = 0;
        curAccelerationSpeed = 0;
    } else if (m_Platform.transform.pos.x > m_Width - m_Platform.transform.size.x) {
        m_Platform.transform.pos.x = m_Width - m_Platform.transform.size.x;
        m_Platform.transform.velocity.x = 0;
        curAccelerationSpeed = 0;
    }

    // Ball movement
    if (m_State == STATE_START) {
        const auto center = m_Platform.getCenter();
        m_Ball.setPosition(center.x - (25.f / 2.f), center.y + 30.f);
    } else {
        const auto ballNextPos = glm::vec3(m_Ball.getCenter(), .1f) + m_Ball.transform.velocity;
        const auto radius = m_Ball.transform.size.y / 2.;
        m_Ball.transform.velocity *= bounceVector(ballNextPos, radius);
        if ((ballNextPos.y - radius) < 0) {
            Start();
            return;
        }
        m_Ball.move(m_Ball.transform.velocity.x, m_Ball.transform.velocity.y);
    }


    if (blinkingColor >= 0.9f || blinkingColor <= 0.6f) colorRate *= -1;
    blinkingColor += colorRate;
    // std::cout << "curAcc: " << curAccelerationSpeed << " curSpeed: " << ballSpeed << '\n';
}

glm::vec3 MyApp::bounceVector(const glm::vec3 ballPos, const float radius) {
    glm::vec3 bVec(1.f, 1.f, 1.f);
    if ((ballPos.x + radius) > m_Width || (ballPos.x - radius) < 0)
        bVec.x = -1;
    if ((ballPos.y + radius) > m_Height)
        bVec.y = -1;
    
    const auto r_ang = radius * 0.75;
    const auto ballT = glm::vec3(ballPos.x, ballPos.y + radius, 0.f);
    const auto ballB = glm::vec3(ballPos.x, ballPos.y - radius, 0.f);
    const auto ballL = glm::vec3(ballPos.x + radius, ballPos.y, 0.f);
    const auto ballR = glm::vec3(ballPos.x - radius, ballPos.y, 0.f);
    const auto ballLT = glm::vec3(ballPos.x + r_ang, ballPos.y + r_ang, 0.f);
    const auto ballRT = glm::vec3(ballPos.x - r_ang, ballPos.y + r_ang, 0.f);
    const auto ballLB = glm::vec3(ballPos.x + r_ang, ballPos.y - r_ang, 0.f);
    const auto ballRB = glm::vec3(ballPos.x - r_ang, ballPos.y - r_ang, 0.f);
    for (int i = 0; i < m_BricksNumber; i++) {
        if (m_Bricks[i].isDead())
            continue;
        if (isInside(ballT, m_Bricks[i].transform) || isInside(ballB, m_Bricks[i].transform) ||
            isInside(ballL, m_Bricks[i].transform) || isInside(ballR, m_Bricks[i].transform) ) {
                if ( abs(ballPos.x - m_Bricks[i].getCenter().x) / m_Bricks[i].transform.size.x >
                     abs(ballPos.y - m_Bricks[i].getCenter().y) / m_Bricks[i].transform.size.y)
                    bVec.x = -1;
                else
                    bVec.y = -1;

                m_Bricks[i].Destroy();
                // return bVec;
            }
        else if (isInside(ballLT, m_Bricks[i].transform) || isInside(ballRT, m_Bricks[i].transform) || 
            isInside(ballLB, m_Bricks[i].transform) || isInside(ballRB, m_Bricks[i].transform)) {
                bVec.x = -1;
                bVec.y = -1;
                m_Bricks[i].Destroy();
            }
    }

    if (isInside(ballT, m_Platform.transform) || isInside(ballB, m_Platform.transform) ||
        isInside(ballL, m_Platform.transform) || isInside(ballR, m_Platform.transform) ) {
        if ( abs(ballPos.x - m_Platform.getCenter().x) / m_Platform.transform.size.x >
                abs(ballPos.y - m_Platform.getCenter().y) / m_Platform.transform.size.y)
            bVec.x = -1;
        else
            bVec.y = -1;
        m_Ball.transform.velocity.x = MIN(10.f, abs(m_Platform.transform.velocity.x)) * sign(m_Platform.transform.velocity.x);
    }

    return bVec;
}

bool MyApp::isInside(glm::vec3 point, Transform target) {
    return (point.x >= target.pos.x && point.x <= target.pos.x + target.size.x) &&
            (point.y >= target.pos.y && point.y <= target.pos.y + target.size.y);
}

// bool MyApp::isColide() {

// }

void MyApp::onDraw() {
    for (int i = 0; i < m_BricksNumber; i++) {
        if(m_Bricks[i].isDead()) {
            if (m_Bricks[i].getDestroyEffRadius() > 0) {
                m_Renderer.UseShader(m_BallShader);
                m_BallShader.setUniformVec2f("u_Center", m_Bricks[i].getCenter());
                m_BallShader.setUniform1f("u_Radius", m_Bricks[i].getDestroyEffRadius());
                m_Bricks[i].setColor(m_Bricks[i].color.r + 0.1f, m_Bricks[i].color.g, m_Bricks[i].color.b, m_Bricks[i].color.a);
                m_Renderer.Draw(m_Bricks[i], m_BallShader);
            } else {
                continue;
            }
        } else {
            m_Bricks[i].setColor(m_Bricks[i].color.r, m_Bricks[i].color.g, blinkingColor, m_Bricks[i].color.a);
            m_Renderer.Draw(m_Bricks[i], m_SimpleShader);
        }
    }

    m_Renderer.Draw(m_Platform, m_SimpleShader);

    m_Renderer.UseShader(m_BallShader);
    m_BallShader.setUniformVec2f("u_Center", m_Ball.getCenter());
    m_BallShader.setUniform1f("u_Radius", m_Ball.transform.size.y / 2.);
    m_Renderer.Draw(m_Ball, m_BallShader);
}

void MyApp::onKeyCallback(int key, int action) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (m_State == STATE_START) {
            m_Ball.transform.velocity.x = MIN(10.f, abs(m_Platform.transform.velocity.x)) * sign(m_Platform.transform.velocity.x);
            m_Ball.transform.velocity.y = 6.f;
            m_State = STATE_GAME;
        } else {
            Start();
        }
    }
}
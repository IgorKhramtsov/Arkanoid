#pragma once

#include "Application.h"
#include "GameObject.h"

#define STATE_START 0
#define STATE_GAME  1

class MyApp : public Application {
private:
    int m_BricksNumber;
    GameObject *m_Bricks = new GameObject[30];
    GameObject m_Platform;
    GameObject m_Ball;
    Shader m_SimpleShader = Shader("assets/brick.vert", "assets/brick.frag");
    Shader m_BallShader = Shader("assets/brick.vert", "assets/ball.frag");

    const int padding_x = 65;
    const int padding_y = 200;
    const int spacing = 10;

    int m_State = STATE_START;

    const float topSpeed = 17.f;
    const float friction = 3.4f;
    const float topAccelerationSpeed = 3.5f;
    const float accelerationSpeed = 0.7f;
    float curAccelerationSpeed = .0f;

    static float MyApp::colorRate;
    static float MyApp::blinkingColor;

    glm::vec3 MyApp::bounceVector(const glm::vec3 ballPos, const float radius);
    bool isInside(glm::vec3 point, Transform target);
public:
  MyApp(const char *title, int width, int height);

  void Start();
  void onUpdate();
  void onDraw();
  void onKeyCallback(int key, int action);
};
#pragma once

#include "Application.h"
#include "GameObject.h"

class MyApp : public Application {
private:
    GameObject *m_Bricks = new GameObject[30];
    GameObject m_Platform;
    GameObject m_Ball;
    Shader m_SimpleShader = Shader("assets/brick.vert", "assets/brick.frag");
    Shader m_BallShader = Shader("assets/brick.vert", "assets/ball.frag");

    int padding_x = 50;
    int padding_y = 200;
    int spacing = 10;
public:
  MyApp(const char *title, int width, int height);

  void Start();
  void onUpdate();
  void onDraw();
  void onKeyCallback(int key, int action);
};
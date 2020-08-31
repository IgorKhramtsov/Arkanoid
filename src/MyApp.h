#pragma once

#include "Application.h"
#include "GameObject.h"
#include <vector>
#include <memory>

class PlatformGO;
class BallGO;
class BrickGO;

enum class State {
  START,
  GAME
};

class MyApp : public Application {
private:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::shared_ptr<PlatformGO> m_Platform;
    std::shared_ptr<BallGO> m_Ball;
    Shader m_SimpleShader = Shader("assets/brick.vert", "assets/brick.frag");
    Shader m_BallShader = Shader("assets/brick.vert", "assets/ball.frag");

    const int padding_x = 65;
    const int padding_y = 200;
    const int spacing = 10;

    State m_State = State::START;

    static inline float MyApp::colorRate = 0.005f;
    static inline float MyApp::blinkingColor = 0.8f;

    bool isInside(glm::vec3 point, Transform target);
public:
  MyApp(const char *title, int width, int height);

  void Start();
  void onUpdate();
  void onDraw();
  void onKeyCallback(int key, int action);
  glm::vec3 MyApp::bounceVector(const glm::vec3 ballPos, const float radius);


  State getState() const;
  const std::shared_ptr<PlatformGO> getPlatform() const;
};
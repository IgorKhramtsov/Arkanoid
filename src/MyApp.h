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
  Shader m_SimpleShader = Shader("assets/simple.vert", "assets/simple.frag");
  Shader m_RoundShader = Shader("assets/simple.vert", "assets/round.frag");

  const int padding_x = 65;
  const int padding_y = 200;
  const int spacing = 10;

  State m_State = State::START;

  bool isInside(glm::vec3 point, Transform target) const;
  void onKeyCallback(int key, int action);
public:
  MyApp(const char *title, int width, int height);

  void Start();
  void onUpdate();
  void onDraw();
  glm::vec3 bounceVector(const glm::vec3 ballPos, const float radius) const;


  State getState() const;
  const std::shared_ptr<PlatformGO> getPlatform() const;
};

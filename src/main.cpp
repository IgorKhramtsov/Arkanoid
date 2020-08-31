/*
  Arkanoid
  - platform moving left\right by keyboard
  - ball bounces out of sides, platform and top
  - bottom is endgame
  - bricks generates randomly on game start
*/

/* Should be done:
  - Review physic
  - Add lerp
  - Review movement
  - Add mouse control
  - Add BatchRendering
  - Rework rendering (move more to vertexes)
  - ECS??
  - Cache shader`s uniforms locations
*/

#include "MyApp.h"

int main(int argc, char** argv) {

  auto app = MyApp("Arkanoid", 800, 600);
  if (!app.isInitialized()) {
    return -1;
  }

  app.Run();
}
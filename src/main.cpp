/*
  Arkanoid
  - platform moving left\right by keyboard
  - ball bounces out of sides, platform and top
  - bottom side is endgame
  - bricks generates randomly on the start
*/

#include "MyApp.h"

int main(int argc, char** argv) {

  auto app = MyApp("Arkanoid", 800, 600);
  if (!app.isInitialized()) {
    return -1;
  }

  app.Run();
}
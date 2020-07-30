Arkanoid
====================

Simple OpenGL Arkanoid game.

  - platform moving left\right by keyboard
  - ball bounces out of walls, platform and top side
  - bottom side is endgame
  - bricks generates randomly on the start

## Build

```
git clone --recursive https://github.com/crataegus27/Arkanoid.git
cd Arkanoid
mkdir build
cd build 
cmake ..
make # your build command dependent on platform
```

## Dependencies

 - [glfw](https://github.com/glfw/glfw)
 - [glew](https://github.com/nigels-com/glew)

 ## Progress

 1. [X] Project initialization (cmake)
 2. [X] Creating a window (glfw)
 3. [ ] Drawing (glew)
 4. [ ] Input control
 5. [ ] Game logic
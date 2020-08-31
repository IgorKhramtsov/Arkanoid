#pragma once

#include "GameObject.h"
#include "MyApp.h"

class PlatformGO : public GameObject {
    int m_WindowWidth;
    int m_WindowHeight;

    const float topSpeed = 17.f;
    const float friction = 3.4f;
    const float topAccelerationSpeed = 3.5f;
    const float accelerationSpeed = 0.7f;
    float curAccelerationSpeed = .0f;

    void OnUpdate(MyApp &);
    
public:
    PlatformGO();
};
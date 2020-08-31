#pragma once

#include "GameObject.h"
#include "MyApp.h"
#include <iostream>

class BrickGO : public GameObject {
// Destroy effect
    float m_Radius;
    float m_RadiusShrink = 3.5f;

    float colorRate = 0.005f;
    float blinkingColor = 0.8f;

public:
    BrickGO(MyApp *app, Renderable r);

    float getDestroyEffRadius();
    void OnUpdate();
    void OnDraw();
};
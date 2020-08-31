#pragma once

#include "GameObject.h"
#include "MyApp.h"
#include <iostream>

class BrickGO : public GameObject {
// Destroy effect
    float m_Radius;
    float m_RadiusShrink = 2.f;

public:
    BrickGO() = default;
    virtual ~BrickGO() {};

    float getDestroyEffRadius();
    GameObject* setRenderable(Renderable r);
    void OnUpdate(MyApp &) {};
};
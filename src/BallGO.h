#pragma once

#include "GameObject.h"
#include "MyApp.h"

class BallGO : public GameObject {

public:
    BallGO(MyApp *app, Renderable r) : GameObject(app, r) {};

    void OnUpdate();
    void OnDraw();
};
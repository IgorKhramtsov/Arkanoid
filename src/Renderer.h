#pragma once

struct RederebaleObj {
    // unsigned int vbo;
    unsigned int vao;
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    RederebaleObj CreateBrick();

    void Draw(RederebaleObj obj);
};

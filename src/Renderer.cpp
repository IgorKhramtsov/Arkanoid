#include "Renderer.h"

#include <GL/glew.h>
#include "utils.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {
    
}

RederebaleObj Renderer::CreateBrick() {
    const float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    const unsigned int indices[] = {
        0, 1, 2, 
        2, 3, 0
    };

    unsigned int vao;
    unsigned int vbo;
    unsigned int ibo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (const void*)vertices, GL_STATIC_DRAW);

    // glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 2 * sizeof(float), 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), (const void*)indices, GL_STATIC_DRAW);

    return { vao };
}

void Renderer::Draw(RederebaleObj obj) {
    GLCALL(glBindVertexArray(obj.vao));
    GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}
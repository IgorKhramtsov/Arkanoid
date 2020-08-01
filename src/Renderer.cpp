#include "Renderer.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils.h"
#include "GameObject.h"

Renderer::Renderer(float width, float height) {
    this->m_Proj = glm::ortho(0.0f, width, 0.0f, height, -1.f, 1.f);
    this->m_View = glm::mat4(1.0f);
}

void Renderer::setClearColor(float v0, float v1, float v2, float v3) { 
        m_ClearColor.r = v0;
        m_ClearColor.g = v1; 
        m_ClearColor.b = v2; 
        m_ClearColor.a = v3; 
}

Renderable Renderer::CreateRect(float w, float h) {
    const float vertices[] = {
        0.f, 0.f,
        w, 0.f,
        w, h,
        0.f, h
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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), (const void*)indices, GL_STATIC_DRAW);

    return { vao, w, h};
}

void Renderer::UseShader(const Shader &shader) {
    if (this->currentShader == shader.getProgramID())
        return;
    this->currentShader = shader.getProgramID();
    shader.Bind();
}

void Renderer::Draw(const GameObject &obj,const Shader &shader) {
    UseShader(shader);
    auto model = glm::translate(glm::mat4(1.0f), obj.transform.pos);
    model = glm::scale(model, obj.transform.scale);
    auto mvp = m_Proj * m_View * model;
    shader.setUniformMat4f("u_MVP", mvp);

    shader.setUniform4f("u_Color", obj.color.r, obj.color.g, obj.color.b, obj.color.a);

    ASSERT(obj.getRenderable().vao != 0);
    GLCALL(glBindVertexArray(obj.getRenderable().vao));
    GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
}
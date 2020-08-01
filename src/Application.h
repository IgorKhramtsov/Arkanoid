#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

class Application {
private:
    static Application *instance;
    GLFWwindow *m_Window;
    bool m_Initialized = false;
    double m_UpdateRate = 1. / 30.;
    
    static void glfw_error_callback(int error, const char* desc);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void gldebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

protected:
    Renderer m_Renderer;
    int m_Width, m_Height;

public:
    Application(const char*, int, int);
    ~Application();

    static Application *getApp() {
        return Application::instance; 
    };

    void Run();

    virtual void onUpdate() = 0;
    virtual void onDraw() = 0;
    virtual void onKeyCallback(int key, int action) = 0;

    Renderer *getRenderer() { return &m_Renderer; };
    bool isInitialized() { return m_Initialized; };
    bool isKeyPressed(int key);
};
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

class Application {
private:
    const static inline double FixedUpdateRate = 1. / 30.;
    const static inline double SlowedFixedUpdateRate = 1.;
          static inline Application *instance;
          static inline GLFWwindow *m_Window;

    bool m_Initialized = false;
    double m_UpdateRate = FixedUpdateRate;
    
    static void glfw_error_callback(int error, const char* desc);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void gldebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

protected:
    Renderer m_Renderer;
    int m_Width, m_Height;

public:
    Application(const char*, int, int);
    ~Application();
    static Application& getApp();

    Renderer& getRenderer();
    void getWindowSize(int&, int&);
    bool isInitialized();
    static bool isKeyPressed(int key);

    void Run();
    void CloseWindow();

    virtual void onKeyCallback(int key, int action) = 0;
    virtual void onUpdate() = 0;
    virtual void onDraw() = 0;
};
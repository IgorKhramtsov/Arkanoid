#include "Application.h"

#include <stdio.h>
#include <iostream>

Application *Application::instance;
Application::Application(const char *title, int width, int height) {
    if (Application::instance == nullptr)
        Application::instance = this;
    else {
        std::cout << "App already initialized!\n";
        return;
    }
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(Application::glfw_error_callback);
    if (!glfwInit()) {
        std::cout << "glfw initialization failed.\n";
        return;
    }

    m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!m_Window) {
        std::cout << "glfw window initialization failed.\n";
        return;
    }
    glfwMakeContextCurrent(m_Window);
    if (glewInit() != 0) {
        std::cout << "glew initialization failed.\n";
        return;
    }
    glfwSetKeyCallback(m_Window, key_callback);
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';

    glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
    glViewport(0, 0, m_Width, m_Height); 
    glfwSwapInterval(1);

    m_Initialized = true;
    m_Renderer = Renderer((float)m_Width, (float)m_Height);
}

Application::~Application() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

void Application::Run() {
    
    auto lastTime = glfwGetTime();
    double curTime;
    double deltaTime = 0.;
    double updateRate = 1. / 40.;

    while(!glfwWindowShouldClose(m_Window)) {
        m_Renderer.Clear();

        curTime = glfwGetTime();
        deltaTime += (curTime - lastTime);
        lastTime = curTime;

        if(deltaTime >= updateRate) {
            onUpdate();
            deltaTime -= updateRate;
        }

        onDraw();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
        
  }
}

bool Application::isKeyPressed(int key) {
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

void Application::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    
    Application::getApp()->onKeyCallback(key, action);
}

void Application::glfw_error_callback(int error, const char* desc) {
  std::cout << "[GLFW] error #" << error << " " << desc << '\n';
}

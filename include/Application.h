#pragma once

#include <stdinc.h>
#include <GLFW/glfw3.h>


class Application
{
public:
    Application();
    ~Application();
    void Run();
protected:
    GLFWwindow* m_window;
    virtual void OnUpdate(float);
    virtual void OnRender();
};

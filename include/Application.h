#pragma once

#include <stdinc.h>
#include <GLFW/glfw3.h>


class Application
{
public:
    Application();
    ~Application();
    void Run();
private:
    GLFWwindow* m_window;
};

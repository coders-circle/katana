#pragma once

#include <GLFW/glfw3.h>
#include <utils/Timer.h>


class Application
{
public:
    Application();
    ~Application();
    void Run();

    Timer& GetTimer() { return m_timer; }

protected:
    GLFWwindow* m_window;
    virtual void OnUpdate(float);
    virtual void OnRender();

    Timer m_timer;
};

#pragma once

#include <GLFW/glfw3.h>
#include <utils/Timer.h>
#include <utils/Input.h>


class Application
{
public:
    Application();
    ~Application();
    void Run();

    Timer& GetTimer() { return m_timer; }

    void SetInput(Input* input)
    {
        m_input = input;
        if (m_input)
            m_input->SetWindowSize(m_width, m_height);
    }
    Input* GetInput() const { return m_input; }

    // Add some default shaders
    void CreateDefaultShaders();

protected:
    GLFWwindow* m_window;
    virtual void OnUpdate(float) {}
    virtual void OnRender() {}
    virtual void OnResize(int width, int height) {}

    Timer m_timer;
    Input* m_input;

    int m_width, m_height;
};

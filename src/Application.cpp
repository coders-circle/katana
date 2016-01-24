#include <stdinc.h>
#include <Application.h>

Application::Application()
    : m_timer(60)
{
    if (!glfwInit())
    {
        throw Exception("Couldn't intiailize GLFW");
    }
    m_window = glfwCreateWindow(800, 600, "Katana Test", 0, 0);
    glfwMakeContextCurrent(m_window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        throw Exception(std::string("Error ")
            + reinterpret_cast<const char*>(glewGetErrorString(GLEW_VERSION)));
    }
    glClearColor(0.396f, 0.612f, 0.937f, 1.0f);

    m_timer.Reset(60);
}


Application::~Application()
{
    glfwTerminate();
}


void Application::OnUpdate(float dt)
{
}


void Application::OnRender()
{
}


void Application::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
        m_timer.Update([this](float dt)
        {
            OnUpdate(dt);
        });
        this->OnRender();
    }
}

#include <Application.h>

Application::Application()
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
        this->OnUpdate(0);
        this->OnRender();
    }
}

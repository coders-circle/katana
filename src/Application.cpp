#include <stdinc.h>
#include <Application.h>


Application::Application() :
    m_timer(60), m_input(0),
    m_width(800), m_height(600)
{
    if (!glfwInit())
    {
        throw Exception("Couldn't intiailize GLFW");
    }

    // Try to set opengl context version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    m_window = glfwCreateWindow(800, 600, "Katana Test", 0, 0);
    glfwSetWindowUserPointer(m_window, this);
    glfwMakeContextCurrent(m_window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        throw Exception(std::string("Error ")
            + reinterpret_cast<const char*>(glewGetErrorString(GLEW_VERSION)));
    }

    m_timer.Reset(60);

    // OpenGL initialization
    glClearColor(0.396f, 0.612f, 0.937f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);


    // Set callbacks
    glfwSetFramebufferSizeCallback(m_window,
        [](GLFWwindow* window, int width, int height)
        {
            Application* app =
                (Application*) glfwGetWindowUserPointer(window);
            app->m_width = width;
            app->m_height = height;

            if (app->m_input)
                app->m_input->SetWindowSize(width, height);
            app->OnResize(width, height);
        }
    );

    glfwSetKeyCallback(m_window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Application* app =
                (Application*) glfwGetWindowUserPointer(window);

            if (app->m_input)
                app->m_input->SetKeyPressed(key,
                    action == GLFW_PRESS || action == GLFW_REPEAT);
        }
    );

    glfwSetCursorPosCallback(m_window,
        [](GLFWwindow* window, double xpos, double ypos)
        {
            Application* app =
                (Application*) glfwGetWindowUserPointer(window);

            if (app->m_input)
                app->m_input->SetCursorPos(xpos, ypos);
        }
    );


    CreateDefaultShaders();
    CreateDefaultTextures();
}


Application::~Application()
{
    glfwTerminate();
}

void Application::Run()
{
    // Call the resize handler once before starting
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    OnResize(width, height);

    // Start the main loop
    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_timer.Update([this](float dt)
        {
            OnUpdate(dt);
        });
        this->OnRender();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}


#include <material/Shader.h>

void Application::CreateDefaultShaders()
{
    auto& sm = Manager<Shader>::GetShared();

    sm.Add("vs_diffuse", "shaders/vs_diffuse.glsl", GL_VERTEX_SHADER);
    sm.Add("fs_diffuse", "shaders/fs_diffuse.glsl", GL_FRAGMENT_SHADER);
}


#include <texture/Texture.h>

void Application::CreateDefaultTextures()
{
    auto& tm = Manager<Texture>::GetShared();

    std::vector<unsigned char> wh;
    for (int i=0; i<4*4; ++i)
        wh.push_back(0xFF);
    tm.Add("white", &wh[0], 1, 1);
}

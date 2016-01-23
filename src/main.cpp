#include <stdinc.h>
#include <GLFW/glfw3.h>


int main()
{
    if (!glfwInit())
    {
        std::cout << "Couldn't intiailize GLFW" << std::endl;
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", 0, 0);
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "Error: " << glewGetErrorString(GLEW_VERSION);
        std::cout << std::endl;
        return -1;
    }

    glClearColor(0.396f, 0.612f, 0.937f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

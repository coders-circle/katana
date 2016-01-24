#include <stdinc.h>
#include <TestApp.h>

#include <ecs/ecs.h>
#include <material/Program.h>


int main()
{
    try
    {
        TestApp app;
        
        Program m(std::vector<Shader> {
            Shader("shaders/vs_test.glsl", GL_VERTEX_SHADER),
            Shader("shaders/fs_test.glsl", GL_FRAGMENT_SHADER),
        });

        app.Run();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

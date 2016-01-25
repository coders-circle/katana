#include <Application.h>
#include <model/Mesh.h>
#include <ecs/ecs.h>
#include <component/Transform.h>
#include <component/Camera.h>


// Test Mesh Data
std::vector<Vertex> vertices = std::vector<Vertex>{
    Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec2(1.0f, 1.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec2(0.0f, 1.0f)),
};

std::vector<GLuint> indices = { 0, 1, 2, 0, 2, 3 };


// Test application
class TestApp: public Application
{
public:
    TestApp() :
        testMesh(vertices, indices),
        testMat("textures/test.jpg"),
        input(800, 600)
    {
        testMat.color = glm::vec4(1,0,0,1);
        camera.Add<Camera>(800, 600);
        camera.Add<Transform>(glm::vec3(0, 0, 2));

        SetInput(&input);
    }

private:
    glm::mat4 modelMat;
    Entity camera;

    TestMaterial testMat;
    Mesh testMesh;

    Input input;

    void OnResize(int width, int height)
    {
        glViewport(0, 0, width, height);
        camera.Get<Camera>()->Set(width, height, 120, 0.1f, 10000.0f);
    }

    void OnRender()
    {
        glm::mat4 vp = camera.Get<Camera>()->GetProjection()
            * camera.Get<Transform>()->GetWorldInverse();
            
        // Draw the test mesh with test material
        testMesh.Draw(&testMat, modelMat, vp);
    }

    void OnUpdate(float dt)
    {
        modelMat =
            glm::rotate(glm::mat4(), m_timer.GetTotalTime(),
                glm::vec3(0, 1, 0)
            );

        if (input.IsKeyPressed(GLFW_KEY_ESCAPE))
            exit(0);
    }
};

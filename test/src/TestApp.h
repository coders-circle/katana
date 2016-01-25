#include <Application.h>
#include <model/Mesh.h>
#include <model/Model.h>
#include <material/DiffuseMaterial.h>

#include <ecs/ecs.h>
#include <component/Transform.h>
#include <component/Camera.h>

#include "Snake.h"


std::vector<Vertex> cubeVertices = std::vector<Vertex>{
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0, 0, 0), glm::vec2(0.0f, 0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0, 0, 0), glm::vec2(1.0f, 0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0, 0, 0), glm::vec2(1.0f, 1.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0, 0, 0), glm::vec2(0.0f, 1.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 0, 0), glm::vec2(0.0f, 0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0, 0, 0), glm::vec2(1.0f, 0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0, 0, 0), glm::vec2(1.0f, 1.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0, 0, 0), glm::vec2(0.0f, 1.0f)),
};

std::vector<GLuint> cubeIndices = {
    0, 1, 2, 0, 2, 3,   // front face
    4, 5, 6, 4, 6, 7,   // back face
    1, 5, 6, 1, 6, 2,   // right face
    0, 4, 7, 0, 7, 3,   // left face
    3, 2, 6, 3, 6, 7,   // top face
    0, 1, 5, 0, 5, 4    // bottom face
};



// Test application
class TestApp: public Application
{
public:
    TestApp() :
        testModel("../model-converter/bin/homer.out"),
        m_input(800, 600)
    {
        m_input.SetWindowSize(800, 600);
        camera.Add<Camera>(800, 600);
        camera.Add<Transform>(glm::vec3(0, 0, 100));
        SetInput(&m_input);
    }

private:
    glm::mat4 modelMat;
    Entity camera;
    Input m_input;

    Model testModel;

    void OnResize(int width, int height)
    {
        m_input.SetWindowSize(width, height);
        glViewport(0, 0, width, height);
        camera.Get<Camera>()->Set(width, height, 120, 0.1f, 10000.0f);
    }

    void OnRender()
    {
        glm::mat4 vp = camera.Get<Camera>()->GetProjection()
            * camera.Get<Transform>()->GetWorldInverse();
            
        // Draw the test model with test material
        testModel.Render(modelMat, vp);
    }

    void OnUpdate(float dt)
    {
        modelMat =
            glm::rotate(glm::mat4(), m_timer.GetTotalTime(),
                glm::vec3(0, 1, 0)
            );

        if (m_input.IsKeyPressed(GLFW_KEY_ESCAPE))
            exit(0);
    }
};


class BlockTestApp: public Application
{
public:
    BlockTestApp()
        :m_input(800, 600)
    {
        cam.Add<Camera>(800, 600);
        cam.Add<Transform>(glm::vec3(0, 10, 60));
        m_timer.Reset(10);
        SetInput(&m_input);
    }
    void OnResize(int width, int height)
    {
        glViewport(0, 0, width, height);
        cam.Get<Camera>()->Set(width, height, 120, 0.1f, 10000.0f);
    }
    void OnRender()
    {
        snake.Render(cam.Get<Camera>()->GetProjection()
            * cam.Get<Transform>()->GetWorldInverse());
    }
    void OnUpdate(float dt)
    {
        if(m_input.IsKeyPressed(GLFW_KEY_LEFT))
            snake.SetDirection(west);
        if(m_input.IsKeyPressed(GLFW_KEY_RIGHT))
            snake.SetDirection(east);
        if(m_input.IsKeyPressed(GLFW_KEY_UP))
            snake.SetDirection(north);
        if(m_input.IsKeyPressed(GLFW_KEY_DOWN))
            snake.SetDirection(south);
        snake.Update(dt);
        if (m_input.IsKeyPressed(GLFW_KEY_ESCAPE))
            exit(0);
    }
private:
    Snake snake;
    Block block;
    Entity cam;

    Input m_input;
};

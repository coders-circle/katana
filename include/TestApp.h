#include <Application.h>
#include <model/Mesh.h>


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
    TestApp()
        : testMesh(vertices, indices),
        testMat("textures/test.jpg")
    {
        testMat.color = glm::vec4(1,0,0,1);
    }

private:
    glm::mat4 modelMat;
    glm::mat4 projection;
    TestMaterial testMat;
    Mesh testMesh;

    void OnResize(int width, int height)
    {
        glViewport(0, 0, width, height);
        projection = glm::perspective(120.0f, float(width)/float(height),
            0.1f, 10000.0f);
        Input::SetWindowSize(width, height);
    }

    void OnRender()
    {
        // Draw the test mesh with test material
        testMesh.Draw(&testMat, modelMat, projection);
    }

    void OnUpdate(float dt)
    {
        if(Input::IsKeyPressed(GLFW_KEY_ESCAPE)){
            exit(0);    
        }
        modelMat =
            glm::translate(glm::mat4(), glm::vec3(0, 0, -2.f)) *
            glm::rotate(glm::mat4(), m_timer.GetTotalTime(),
                glm::vec3(0, 1, 0));
    }
};

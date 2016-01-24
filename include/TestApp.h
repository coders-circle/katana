#include <Application.h>
#include <material/Material.h>


class TestApp: public Application
{
public:
    TestApp()
    {
        GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
        };

        GLuint VBO;
        glGenBuffers(1, &VBO);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        test.color = glm::vec4(1,0,0,1);
    }

private:
    TestMaterial test;
    GLuint VAO;
    glm::mat4 model;

    void OnRender()
    {
        test.Use();

        Program& p = test.GetProgram();
        if (p.DoUseStdTransforms())
        {
            p.SetUniform("mvp", model);
            p.SetUniform("model", model);
        }
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    void OnUpdate(float dt)
    {
        model = glm::rotate(glm::mat4(), m_timer.GetTotalTime(),
            glm::vec3(0, 1, 0));
        // std::cout << dt << " seconds passed" << std::endl;
    }
};

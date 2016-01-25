#pragma once
#include <ecs/Component.h>


// Perspective camera component
class Camera : public ComponentBase<Camera>
{
public:
    Camera(float width, float height,
        float fov=120, float near=0.1f, float far=10000.0f)
            : m_fov(fov), m_near(near), m_far(far),
            m_width(width), m_height(height)
    {
        Calculate();
    }

    // Camera properties

    float GetFOV() const { return m_fov; }
    float GetNearPlane() const { return m_near; }
    float GetFarPlane() const { return m_far; }
    float GetWidth() const { return m_width; }
    float GetHeight() const { return m_height; }

    void SetFOV(float fov) { m_fov = fov; Calculate(); }
    void SetNearPlane(float near) { m_near = near; Calculate(); }
    void SetFarPlane(float far) { m_far = far; Calculate(); }
    void SetWidth(float width) { m_width = width; Calculate(); }
    void SetHeight(float height) { m_height = height; Calculate(); }

    void Set(float width, float height,
        float fov, float near, float far)
    {
        m_width = width;
        m_height = height;
        m_fov = fov;
        m_near = near;
        m_far = far;
        Calculate();
    }

    // Projection matrix
    const glm::mat4& GetProjection() const { return m_projection; }

    // Get combined view projection matrix for given transformation
    // const glm::mat4& GetViewProjection const (const glm::mat4& transform)
    // {
    //     return GetView(transform);
    // }


private:
    float m_fov, m_near, m_far;
    float m_width, m_height;

    glm::mat4 m_projection;

    void Calculate()
    {
        m_projection = glm::perspective(m_fov,
            m_width/m_height, m_near, m_far);
    }
};

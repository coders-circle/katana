#pragma once

#include "Block.h"

enum Direction { east, west, north, south };

class Snake
{
public:
    Snake():
        m_speed(0.0f),
        m_direction(north)
    {
        m_body.resize(50);
        for(int i = 0; i < m_body.size(); i++)
        {
            m_body[i].SetPosition(glm::vec3(0, 0, i));
        }
    }
    void Update(float dt)
    {
        glm::vec3 headPos = m_body[0].GetPosition();
        switch(m_direction)
        {
            case east:
                headPos.x += 1;
                break;
            case west:
                headPos.x -= 1;
                break;
            case north:
                headPos.z -= 1;
                break;
            case south:
                headPos.z += 1;
                break;
        }
        m_body[0].SetPosition(headPos);
        this->AdjustBody();
    }
    void SetDirection(int newDirection)
    {
        m_direction = newDirection;
    }
    void Render(glm::mat4 vp)
    {
        for(auto& block: m_body)
        {
            block.Render(vp);
        }
    }
private:
    std::vector<Block> m_body;
    int m_direction;
    float m_speed;

    void AdjustBody()
    {
        for(int i = m_body.size()-1; i > 0; i--)
        {
            m_body[i].SetPosition(m_body[i-1].GetPosition());
        }
    }
};

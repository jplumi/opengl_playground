#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    void Update(float deltaTime);
    glm::mat4 GetViewMatrix();

private:
    glm::vec2 m_Position = glm::vec2(0.0f);
    float m_Speed = 100.0f;
};


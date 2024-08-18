#pragma once

#include <glm/glm.hpp>

class Camera2D
{
public:
    glm::vec3 position = glm::vec3(0.0f);

    void Update(float deltaTime);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

private:
    float m_Speed = 120.0f;
    float m_Zoom = 1;
};


#pragma once

#include <glm/glm.hpp>

class Camera2D
{
public:
    glm::vec3 position = glm::vec3(0.0f);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    
    void Zoom(float amount);

private:
    float m_Speed = 120.0f;
    float m_Zoom = 1;
};


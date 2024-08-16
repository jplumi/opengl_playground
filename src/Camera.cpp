#include "Camera.hpp"

#include "InputManager.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Camera::Update(float deltaTime)
{
    if(InputManager::GetKey(GLFW_KEY_W))
    {
        m_Position.y += deltaTime * m_Speed;
    }
    if(InputManager::GetKey(GLFW_KEY_S))
    {
        m_Position.y -= deltaTime * m_Speed;
    }
    if(InputManager::GetKey(GLFW_KEY_A))
    {
        m_Position.x -= deltaTime * m_Speed;
    }
    if(InputManager::GetKey(GLFW_KEY_D))
    {
        m_Position.x += deltaTime * m_Speed;
    }
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::translate(glm::mat4(1.0f), glm::vec3(-m_Position.x, -m_Position.y, 0));
}


#include "Camera2D.hpp"

#include "Application.hpp"
#include "InputManager.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Camera2D::Update(float deltaTime)
{
    if(InputManager::GetKey(GLFW_KEY_W))
    {
        position.y += deltaTime * m_Speed;
    }
    if(InputManager::GetKey(GLFW_KEY_S))
    {
        position.y -= deltaTime * m_Speed;
    }
    if(InputManager::GetKey(GLFW_KEY_A))
    {
        position.x -= deltaTime * m_Speed;
    }
    if(InputManager::GetKey(GLFW_KEY_D))
    {
        position.x += deltaTime * m_Speed;
    }
    MouseScrollEvent scrollEvent = InputManager::GetMouseScroll();
    if(scrollEvent.scrolled)
    {
        m_Zoom = std::fmax(m_Zoom + scrollEvent.amount, 1.0f);
    }
}

glm::mat4 Camera2D::GetViewMatrix()
{
    return glm::translate(glm::mat4(1.0f), -position);
}

glm::mat4 Camera2D::GetProjectionMatrix()
{
    WindowSettings settings = Application::windowSettings;
    float zoom = 2 * m_Zoom;
    return glm::ortho(
        -settings.width/zoom, settings.width/zoom,
        -settings.height/zoom, settings.height/zoom, -1.0f, 1.0f);
}


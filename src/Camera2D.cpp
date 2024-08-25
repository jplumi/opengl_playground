#include "Camera2D.hpp"

#include "Application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

void Camera2D::Zoom(float amount)
{
    m_Zoom = std::fmax(m_Zoom + amount, 0.5f);
}


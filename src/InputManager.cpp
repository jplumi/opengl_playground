#include "InputManager.hpp"

bool InputManager::m_InputKeys[500];
MouseScrollEvent InputManager::m_ScrollInput = { false, 0 };

void InputManager::Init(GLFWwindow* window)
{
    glfwSetKeyCallback(window, InputManager::GlfwKeyCallback);
    glfwSetScrollCallback(window, InputManager::GlfwMouseScrollCallback);
}

void InputManager::HandleInput()
{
    glfwPollEvents();
}

MouseScrollEvent InputManager::GetMouseScroll() 
{
    MouseScrollEvent event = m_ScrollInput;
    m_ScrollInput.scrolled = false;
    return event;
}

void InputManager::GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        m_InputKeys[key] = true;
    else if(action == GLFW_RELEASE)
        m_InputKeys[key] = false;
}

void InputManager::GlfwMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    m_ScrollInput.scrolled = true;
    m_ScrollInput.amount = yoffset;
}

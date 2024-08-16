#include "InputManager.hpp"
#include "GLFW/glfw3.h"

bool InputManager::m_InputKeys[500];

void InputManager::Init(GLFWwindow* window)
{
    glfwSetKeyCallback(window, InputManager::GlfwKeyCallback);
}

void InputManager::HandleInput()
{
    glfwPollEvents();
}

bool InputManager::GetKey(int keyCode)
{
    return m_InputKeys[keyCode];
}

void InputManager::GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        m_InputKeys[key] = true;
    else if(action == GLFW_RELEASE)
        m_InputKeys[key] = false;
}


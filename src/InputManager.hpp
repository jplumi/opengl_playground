#pragma once

#include "GLFW/glfw3.h"

class InputManager
{
public:
    static void Init(GLFWwindow* window);
    static void HandleInput();

    static bool GetKey(int keyCode);

private:
    static bool m_InputKeys[500];

    static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};


#pragma once

#include <GLFW/glfw3.h>

struct MouseScrollEvent
{
    bool scrolled;
    float amount;
};

class InputManager
{
public:
    static void Init(GLFWwindow* window);
    static void HandleInput();

    static inline bool GetKey(int keyCode) { return m_InputKeys[keyCode]; }
    static MouseScrollEvent GetMouseScroll();

private:
    static bool m_InputKeys[500];
    static MouseScrollEvent m_ScrollInput;

    static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void GlfwMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};


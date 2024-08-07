#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Settings.hpp"

class Application
{
public:
    static void Init();
    static void Run();
    static void Shutdown();

    static const WindowSettings windowSettings;

private:
    static GLFWwindow* m_Window;
};


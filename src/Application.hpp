#pragma once

#include "Camera.hpp"
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
    static Camera camera;

private:
    static GLFWwindow* m_Window;
};


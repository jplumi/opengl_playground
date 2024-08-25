#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer2D.hpp"
#include "Settings.hpp"
#include "Camera2D.hpp"

class Application
{
public:
    static void Init();
    static void Run();
    static void Shutdown();

    static const WindowSettings windowSettings;
    static Camera2D camera;
    static Renderer2D* renderer;

private:
    static GLFWwindow* m_Window;
};


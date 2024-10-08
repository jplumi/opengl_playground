#include "Application.hpp"

#include "GLFW/glfw3.h"
#include "InputManager.hpp"
#include "OpenGLDebug.hpp"
#include "Renderer2D.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Assets.hpp"
#include "tests/TestBatching.hpp"
#include "tests/TestClearColor.hpp"
#include "tests/TestMenu.hpp"
#include "tests/TestTexture.hpp"
#include <iostream>

const WindowSettings Application::windowSettings;
GLFWwindow* Application::m_Window;
Camera2D Application::camera;
Renderer2D* Application::renderer = nullptr;

void Application::Init()
{
    if(!glfwInit())
    {
        std::cout << "Error initializing glfw\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(windowSettings.width, windowSettings.height, windowSettings.title, NULL, NULL);
    if(m_Window == NULL)
    {
        std::cout << "Error creating window\n";
        return;
    }
    glfwMakeContextCurrent(m_Window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error initializing glad\n";
        return;
    }

    GLCall(glViewport(0, 0, windowSettings.width, windowSettings.height));

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplOpenGL3_Init("#version 410");

    ImGui::StyleColorsDark();

    Assets::Init();
    InputManager::Init(m_Window);
    renderer = new Renderer2D(camera);
}

void Application::Run()
{
    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;
    
    testMenu->RegisterTest<test::TestTexture>("texture test");
    testMenu->RegisterTest<test::TestClearColor>("Clear color test");
    testMenu->RegisterTest<test::TestBatching>("Batching test");

    float deltaTime = 0;
    float lastFrameTime = 0;

    while(!glfwWindowShouldClose(m_Window))
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        InputManager::HandleInput();

        if(InputManager::GetKey(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(m_Window, true);

        renderer->Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if(currentTest)
        {
            currentTest->Update(deltaTime);
            currentTest->Render(*renderer);
            ImGui::Begin("Test");
            if(currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->ImGuiRender();
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window);
    }

    if(testMenu != currentTest)
        delete testMenu;
    delete currentTest;
}

void Application::Shutdown()
{
    Assets::Clear();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}


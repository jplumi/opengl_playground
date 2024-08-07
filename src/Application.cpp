#include "Application.hpp"

#include "OpenGLDebug.hpp"
#include "Renderer.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Assets.hpp"
#include "tests/TestBatching.hpp"
#include "tests/TestClearColor.hpp"
#include "tests/TestMenu.hpp"
#include "tests/TestTexture.hpp"
#include <iostream>

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

const WindowSettings Application::windowSettings;
GLFWwindow* Application::m_Window;

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

    glfwSetKeyCallback(m_Window, glfwKeyCallback);

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
}

void Application::Run()
{

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;
    
    testMenu->RegisterTest<test::TestTexture>("texture test");
    testMenu->RegisterTest<test::TestClearColor>("Clear color test");
    testMenu->RegisterTest<test::TestBatching>("Batching test");

    while(!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();
        Renderer::Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if(currentTest)
        {
            currentTest->Update(0.0);
            currentTest->Render();
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


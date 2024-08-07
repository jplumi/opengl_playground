#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Assets.hpp"
#include "Renderer.hpp"
#include "Settings.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "tests/Test.hpp"
#include "tests/TestBatching.hpp"
#include "tests/TestMenu.hpp"
#include "tests/TestTexture.hpp"
#include "tests/TestClearColor.hpp"

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

GLFWwindow* window;

int main()
{
    if(!glfwInit())
    {
        std::cout << "Error initializing glfw\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(g_WindowSettings.width, g_WindowSettings.height, g_WindowSettings.title, NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Error creating window\n";
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, glfwKeyCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error initializing glad\n";
        return -1;
    }

    GLCall(glViewport(0, 0, g_WindowSettings.width, g_WindowSettings.height));

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplOpenGL3_Init("#version 410");

    ImGui::StyleColorsDark();

    Assets::Init();

    Renderer renderer;

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;
    
    testMenu->RegisterTest<test::TestTexture>("texture test");
    testMenu->RegisterTest<test::TestClearColor>("Clear color test");
    testMenu->RegisterTest<test::TestBatching>("Batching test");

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        renderer.Clear();

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

        glfwSwapBuffers(window);
    }

    if(testMenu != currentTest)
        delete testMenu;
    delete currentTest;

    Assets::Clear();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}


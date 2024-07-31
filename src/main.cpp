#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Assets.hpp"
#include "Renderer.hpp"
#include "Settings.hpp"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "tests/Test.hpp"
#include "tests/TestTexture.hpp"

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

WindowSettings windowSettings;

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

    window = glfwCreateWindow(windowSettings.width, windowSettings.height, windowSettings.title, NULL, NULL);
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

    glViewport(0, 0, windowSettings.width, windowSettings.height);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplOpenGL3_Init("#version 410");

    ImGui::StyleColorsDark();

    Assets::Init();

    Renderer renderer;

    test::Test* test = new test::TestTexture();

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        renderer.Clear();

        test->Update(0.0f);
        test->Render(renderer);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        test->ImGuiRender();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    delete test;

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


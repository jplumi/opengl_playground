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
    
    // glm::mat4 projection = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, -1.0f, 1.0f);
    // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    //
    // Shader m_Shader = Assets::LoadShader("base", "vBase.glsl", "fBase.glsl");
    // std::cout << "1\n"; renderer.GLCheckError();
    // m_Shader.Bind();
    // std::cout << "2\n"; renderer.GLCheckError();
    // m_Shader.SetVec3("u_Color", 1.0f, 1.0f, 1.0f);
    // m_Shader.SetInt("u_Texture", 0);
    // m_Shader.SetMat4("u_Projection", projection);
    // m_Shader.SetMat4("u_View", view);
    //
    // Texture m_Texture = Assets::LoadTexture("texture", "images/player.png");
    // m_Texture.Bind();
    // 
    // // ====== BUFFERS
    // float vertices[] = {
    //     50.0f,  50.0f,  1.0f, 1.0f,   // top right
    //     50.0f, -50.0f,  1.0f, 0.0f,   // bottom right
    //     -50.0f, -50.0f, 0.0f, 0.0f,   // bottom left
    //     -50.0f,  50.0f, 0.0f, 1.0f,   // top left 
    // };
    // unsigned int indices[] = {
    //     0, 1, 3,
    //     1, 2, 3
    // };
    //
    // VertexArray* m_VAO = new VertexArray();
    //
    // VertexBuffer* m_VBO = new VertexBuffer(vertices, sizeof(vertices));
    // IndexBuffer* m_EBO = new IndexBuffer(indices, sizeof(indices));
    //
    // VertexBufferLayout vertexLayout;
    // vertexLayout.Push(GL_FLOAT, 2);
    // vertexLayout.Push(GL_FLOAT, 2);
    //
    // m_VAO->AddBuffer(*m_VBO, vertexLayout);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        renderer.Clear();

        // m_Texture.Bind();
        // glm::mat4 model(1.0f);
        // model = glm::translate(model, glm::vec3(0));
        // m_Shader.Bind();
        // m_Shader.SetMat4("u_Model", model);
        // renderer.Draw(*m_VAO, *m_EBO, m_Shader);

        test->Update(0.0f);
        test->Render(renderer);
        // test->ImGuiRender();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // test->ImGuiRender();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    delete test;
    // delete m_VAO;
    // delete m_VBO;
    // delete m_EBO;

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


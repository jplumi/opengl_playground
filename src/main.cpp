#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Assets.hpp"
#include "Renderer.hpp"
#include "Settings.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error initializing glad\n";
        return -1;
    }

    glViewport(0, 0, windowSettings.width, windowSettings.height);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetKeyCallback(window, glfwKeyCallback);

    // ====== IMGUI

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplOpenGL3_Init("#version 410");

    ImGui::StyleColorsDark();
    
    // ====== MATRICES

    // glm::mat4 projection = glm::ortho(-w/2, w/2, h/2, -h/2, -1.0f, 1.0f);
    // glm::mat4 projection = glm::ortho(-450.0f, 450.0f, -450.0f, 450.0f, -1.0f, 1.0f);
    glm::mat4 projection = glm::ortho(
        -(float)windowSettings.width/2,
        (float)windowSettings.width/2,
        -(float)windowSettings.height/2,
        (float)windowSettings.height/2,
        -1.0f, 1.0f);

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    Assets::Init();

    // ====== TEXTURE

    Texture texture = Assets::LoadTexture("texture", "images/player.png");
    texture.Bind();

    // ====== SHADER

    Shader baseShader = Assets::LoadShader("base", "vBase.glsl", "fBase.glsl");
    baseShader.Bind();
    baseShader.SetVec3("color", 0.2f, 0.5f, 0.8f);
    baseShader.SetInt("u_Texture", 0);
    baseShader.SetMat4("u_Projection", projection);
    baseShader.SetMat4("u_View", view);

    // ====== BUFFERS
    float vertices[] = {
        100.0f,  100.0f,  1.0f, 1.0f,   // top right
        100.0f, -100.0f,  1.0f, 0.0f,   // bottom right
        -100.0f, -100.0f, 0.0f, 0.0f,   // bottom left
        -100.0f,  100.0f, 0.0f, 1.0f,   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    VertexArray VAO;

    VertexBuffer VBO(vertices, sizeof(vertices));
    IndexBuffer EBO(indices, sizeof(indices));

    VertexBufferLayout vertexLayout;
    vertexLayout.Push(GL_FLOAT, 2);
    vertexLayout.Push(GL_FLOAT, 2);

    VAO.AddBuffer(VBO, vertexLayout);

    Renderer renderer;

    glm::vec3 translation(0, 0, 0);
    glm::vec3 scale(1, 1, 1);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glm::mat4 model(1.0f);
        model = glm::scale(model, scale);
        model = glm::translate(model, translation);

        baseShader.SetMat4("u_Model", model);

        renderer.Draw(VAO, EBO, baseShader);

        {
            ImGui::Begin("Settings");                          // Create a window called "Hello, world!" and append into it.
            
            ImGui::SliderFloat2("Position", &translation.x, -500.0f, 500.0f);
            ImGui::SliderFloat2("Scale", &scale.x, 0.0f, 10.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

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


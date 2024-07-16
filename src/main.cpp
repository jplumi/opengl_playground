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

    Assets::Init();

    // ====== TEXTURE

    Texture texture = Assets::LoadTexture("texture", "images/player.png");
    texture.Bind();

    // ====== SHADER

    Shader baseShader = Assets::LoadShader("base", "vBase.glsl", "fBase.glsl");
    baseShader.Bind();
    baseShader.SetVec3("color", 0.2f, 0.5f, 0.8f);
    baseShader.SetInt("u_Texture", 0);

    // ====== BUFFERS
    float vertices[] = {
        0.5f,  0.5f,  1.0f, 1.0f,   // top right
        0.5f, -0.5f,  1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f,   // top left 
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

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        renderer.Clear();

        renderer.Draw(VAO, EBO, baseShader);

        glfwSwapBuffers(window);
    }

    Assets::Clear();

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


#include "TestTexture.hpp"

#include "Assets.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "VertexArray.hpp"
#include <glad/glad.h>
#include <iostream>
#include "imgui/imgui.h"

namespace test {

TestTexture::TestTexture()
    : m_Translation(glm::vec3(0.0f)) 
{
    glm::mat4 projection = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    m_Shader = Assets::LoadShader("base", "vBase.glsl", "fBase.glsl");
    m_Shader.Bind();
    m_Shader.SetVec3("u_Color", 1.0f, 1.0f, 1.0f);
    m_Shader.SetInt("u_Texture", 0);
    m_Shader.SetMat4("u_Projection", projection);
    m_Shader.SetMat4("u_View", view);

    m_Texture = Assets::LoadTexture("texture", "images/player.png");
    m_Texture.Bind();
    
    // ====== BUFFERS
    float vertices[] = {
        50.0f,  50.0f,  1.0f, 1.0f,   // top right
        50.0f, -50.0f,  1.0f, 0.0f,   // bottom right
        -50.0f, -50.0f, 0.0f, 0.0f,   // bottom left
        -50.0f,  50.0f, 0.0f, 1.0f,   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    m_VAO = new VertexArray();

    m_VBO = new VertexBuffer(vertices, sizeof(vertices));
    m_EBO = new IndexBuffer(indices, sizeof(indices));

    VertexBufferLayout vertexLayout;
    vertexLayout.Push(GL_FLOAT, 2);
    vertexLayout.Push(GL_FLOAT, 2);

    m_VAO->AddBuffer(*m_VBO, vertexLayout);
}

TestTexture::~TestTexture()
{
    std::cout << "delete test\n";
    delete m_VAO;
    delete m_VBO;
    delete m_EBO;
}

void TestTexture::Update(float deltaTime)
{
   
}

void TestTexture::Render(const Renderer& renderer)
{
    m_Texture.Bind();

    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Translation);
    m_Shader.Bind();
    m_Shader.SetMat4("u_Model", model);

    renderer.Draw(*m_VAO, *m_EBO, m_Shader);
}

void TestTexture::ImGuiRender()
{
    ImGui::SliderFloat2("Position", &m_Translation.x, -500.0f, 500.0f);
}

}


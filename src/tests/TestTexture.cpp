#include "TestTexture.hpp"

#include "Assets.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "VertexArray.hpp"
#include <cstring>
#include <glad/glad.h>
#include "imgui/imgui.h"
#include "Settings.hpp"

namespace test {

TestTexture::TestTexture()
    : m_Translation(glm::vec3(0.0f)) 
{
    glm::mat4 projection = glm::ortho(
        -g_WindowSettings.width / 2, g_WindowSettings.width / 2,
        -g_WindowSettings.height / 2, g_WindowSettings.height / 2, -1.0f, 1.0f);

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    
    m_Shader = Assets::LoadShader("textureShader", "vert_Texture2D.glsl", "frag_Texture2D.glsl");
    m_Shader->Bind();
    m_Shader->SetVec3("u_Color", 1.0f, 1.0f, 1.0f);
    m_Shader->SetInt("u_Texture", 0);
    m_Shader->SetMat4("u_Projection", projection);
    m_Shader->SetMat4("u_View", view);

    m_Texture = Assets::LoadTexture("images/player.png");
    m_Texture->Bind();

    unsigned int indices[] = {0, 1, 3, 1, 2, 3};

    auto quad1 = VertexArray::CreateQuad(-50.0f, 50.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    Vertex vertices[4];
    memcpy(vertices, quad1.data(), quad1.size() * sizeof(Vertex));

    m_VAO = new VertexArray();

    m_VBO = new VertexBuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    m_EBO = new IndexBuffer(indices, sizeof(indices));

    VertexBufferLayout vertexLayout;
    vertexLayout.Push(GL_FLOAT, 2); // position
    vertexLayout.Push(GL_FLOAT, 2); // tex coords;
    vertexLayout.Push(GL_FLOAT, 3); // color

    m_VAO->AddBuffer(*m_VBO, vertexLayout);
}

TestTexture::~TestTexture()
{
    delete m_VAO;
    delete m_VBO;
    delete m_EBO;
}

void TestTexture::Render()
{
    // m_Texture->Bind();

    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Translation);
    m_Shader->Bind();
    m_Shader->SetMat4("u_Model", model);

    Renderer::Draw(*m_VAO, *m_EBO, *m_Shader);
}

void TestTexture::ImGuiRender()
{
    ImGui::SliderFloat2("Position", &m_Translation.x, -500.0f, 500.0f);
}

}


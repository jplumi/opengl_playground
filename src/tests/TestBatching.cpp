#include "TestBatching.hpp"

#include "Assets.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "VertexArray.hpp"
#include <cstring>
#include <glad/glad.h>
#include "glm/fwd.hpp"
#include "imgui/imgui.h"
#include "Settings.hpp"

namespace test {

TestBatching::TestBatching()
    : m_Translation(glm::vec3(0.0f)) 
{
    glm::mat4 projection = glm::ortho(
        -g_WindowSettings.width/2, g_WindowSettings.width/2,
        -g_WindowSettings.height/2, g_WindowSettings.height/2, -1.0f, 1.0f);

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    
    m_Shader = Assets::LoadShader("baseShader", "vert_Base.glsl", "frag_Base.glsl");
    m_Shader->Bind();
    m_Shader->SetVec3("u_Color", 1.0f, 1.0f, 1.0f);
    m_Shader->SetMat4("u_Projection", projection);
    m_Shader->SetMat4("u_View", view);
 
    auto quad1 = VertexArray::CreateQuad(-50.0f, 50.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    auto quad2 = VertexArray::CreateQuad(50.0f, 50.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    Vertex vertices[8];
    memcpy(vertices, quad1.data(), quad1.size() * sizeof(Vertex));
    memcpy(vertices + quad1.size(), quad2.data(), quad2.size() * sizeof(Vertex));

    unsigned int indices[] = {
        0, 1, 3, 1, 2, 3,
        4, 5, 7, 5, 6, 7 
    };

    m_VAO = new VertexArray();

    m_VBO = new VertexBuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    m_EBO = new IndexBuffer(indices, sizeof(indices));

    VertexBufferLayout vertexLayout;
    vertexLayout.Push(GL_FLOAT, 2); // position
    vertexLayout.Push(GL_FLOAT, 2); // tex coords;
    vertexLayout.Push(GL_FLOAT, 3); // color

    m_VAO->AddBuffer(*m_VBO, vertexLayout);
}

TestBatching::~TestBatching()
{
    delete m_VAO;
    delete m_VBO;
    delete m_EBO;
}

void TestBatching::Render()
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Translation);
    m_Shader->Bind();
    m_Shader->SetMat4("u_Model", model);

    Renderer::Draw(*m_VAO, *m_EBO, *m_Shader);
}

void TestBatching::ImGuiRender()
{
    ImGui::SliderFloat2("Position", &m_Translation.x, -500.0f, 500.0f);
}

}


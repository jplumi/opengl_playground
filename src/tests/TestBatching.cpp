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
#include "Application.hpp"

namespace test {


static std::array<Vertex, 4> CreateQuad(float x, float y, glm::vec3 color, float size = 50.0f);

TestBatching::TestBatching()
{
    WindowSettings settings = Application::windowSettings;
    glm::mat4 projection = glm::ortho(
        -settings.width/2, settings.width/2,
        -settings.height/2, settings.height/2, -1.0f, 1.0f);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f));

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    
    m_Shader = Assets::LoadShader("baseShader", "vert_Base.glsl", "frag_Base.glsl");
    m_Shader->Bind();
    m_Shader->SetVec3("u_Color", 1.0f, 1.0f, 1.0f);
    m_Shader->SetMat4("u_Projection", projection);
    m_Shader->SetMat4("u_View", view);
    m_Shader->SetMat4("u_Model", model);

    unsigned int indices[] = {
        0, 1, 3, 1, 2, 3,
        4, 5, 7, 5, 6, 7 
    };

    m_VAO = new VertexArray();

    m_VBO = new VertexBuffer(nullptr, 1000 * sizeof(Vertex), GL_DYNAMIC_DRAW);
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
    m_Shader->Bind();

    auto quad1 = CreateQuad(m_Position1.x, m_Position1.y, glm::vec3(1.0f, 1.0f, 1.0f));
    auto quad2 = CreateQuad(m_Position2.x, m_Position2.y, glm::vec3(1.0f, 0.0f, 0.0f));

    Vertex vertices[8];
    memcpy(vertices, quad1.data(), quad1.size() * sizeof(Vertex));
    memcpy(vertices + quad1.size(), quad2.data(), quad2.size() * sizeof(Vertex));

    m_VAO->Bind();
    m_EBO->Bind();

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);

    Renderer::Draw(*m_VAO, *m_EBO, *m_Shader);
}

void TestBatching::ImGuiRender()
{
    ImGui::SliderFloat2("Position 1", &m_Position1.x, -500.0f, 500.0f);
    ImGui::SliderFloat2("Position 2", &m_Position2.x, -500.0f, 500.0f);
}

std::array<Vertex, 4> CreateQuad(float x, float y, glm::vec3 color, float size)
{
    Vertex v0;
    v0.position = {x, y};
    v0.texCoords = {0.0f, 0.0f};
    v0.color = color;

    Vertex v1;
    v1.position = {x + size, y};
    v1.texCoords = {1.0f, 0.0f};
    v1.color = color;

    Vertex v2;
    v2.position = {x + size, y + size};
    v2.texCoords = {1.0f, 1.0f};
    v2.color = color;

    Vertex v3;
    v3.position = {x, y + size};
    v3.texCoords = {0.0f, 1.0f};
    v3.color = color;

    return { v0, v1, v2, v3 };
}

}


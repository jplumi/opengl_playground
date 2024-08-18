#include "TestTexture.hpp"

#include "Application.hpp"
#include "Assets.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "VertexArray.hpp"
#include <cstring>
#include <glad/glad.h>
#include "imgui/imgui.h"
#include "Settings.hpp"

namespace test {

struct Vertex
{
    glm::vec2 position;
    glm::vec2 texCoords;
    glm::vec3 color;
};

static std::array<Vertex, 4> CreateQuad(float x, float y, glm::vec3 color, float size = 50.0f);

TestTexture::TestTexture()
    : m_Translation(glm::vec3(0.0f)) 
{
    WindowSettings settings = Application::windowSettings;
    glm::mat4 projection = glm::ortho(
        -settings.width / 2, settings.width / 2,
        -settings.height / 2, settings.height / 2, -1.0f, 1.0f);

    Application::camera.position = glm::vec3(0);
    glm::mat4 view = Application::camera.GetViewMatrix();
    
    m_Shader = Assets::LoadShader("textureShader", "vert_Texture2D.glsl", "frag_Texture2D.glsl");
    m_Shader->Bind();
    m_Shader->SetVec3("u_Color", 1.0f, 1.0f, 1.0f);
    m_Shader->SetInt("u_Texture", 0);
    m_Shader->SetMat4("u_Projection", Application::camera.GetProjectionMatrix());
    m_Shader->SetMat4("u_View", view);

    m_Texture = Assets::LoadTexture("images/player.png");
    m_Texture->Bind();

    unsigned int indices[] = {0, 1, 3, 1, 2, 3};

    auto quad1 = CreateQuad(-50.0f, 50.0f, glm::vec3(1.0f, 1.0f, 1.0f));

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
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Translation);
    m_Shader->Bind();
    m_Shader->SetMat4("u_Model", model);
    m_Shader->SetMat4("u_View", Application::camera.GetViewMatrix());
    m_Shader->SetMat4("u_Projection", Application::camera.GetProjectionMatrix());

    Renderer::Draw(*m_VAO, *m_EBO, *m_Shader);
}

void TestTexture::ImGuiRender()
{
    ImGui::SliderFloat2("Position", &m_Translation.x, -500.0f, 500.0f);
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



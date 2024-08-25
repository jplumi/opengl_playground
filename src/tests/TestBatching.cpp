#include "TestBatching.hpp"

#include "Assets.hpp"
#include "IndexBuffer.hpp"
#include "InputManager.hpp"
#include "OpenGLDebug.hpp"
#include "VertexArray.hpp"
#include <cstring>
#include <glad/glad.h>
#include "glm/fwd.hpp"
#include "imgui/imgui.h"
#include "Application.hpp"

namespace test {

static Vertex* CreateQuad(Vertex* target, float x, float y, glm::vec3 color, float size = 50);

TestBatching::TestBatching()
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f));

    Application::camera.position = glm::vec3(0);
    glm::mat4 view = Application::camera.GetViewMatrix();
    
    m_Shader = Assets::LoadShader("baseShader", "vert_Base.glsl", "frag_Base.glsl");
    m_Shader->Bind();
    m_Shader->SetVec3("u_Color", 1.0f, 1.0f, 1.0f);
    m_Shader->SetMat4("u_Projection", Application::camera.GetProjectionMatrix());
    m_Shader->SetMat4("u_View", view);
    m_Shader->SetMat4("u_Model", model);

    const size_t maxQuadsCount = 1000;
    const size_t maxVertexCount = maxQuadsCount * 4;
    const size_t maxIndexCount = maxQuadsCount * 6;

    unsigned int indices[maxIndexCount];
    unsigned int offset = 0;
    for(size_t i = 0; i < maxIndexCount; i += 6)
    {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 3 + offset;

        indices[i + 3] = 1 + offset;
        indices[i + 4] = 2 + offset;
        indices[i + 5] = 3 + offset;

        offset += 4;
    }

    m_VAO = new VertexArray();

    m_VBO = new VertexBuffer(nullptr, maxVertexCount * sizeof(Vertex), GL_DYNAMIC_DRAW);
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

void TestBatching::Update(float deltaTime)
{
    float cameraSpeed = 120.0f;
    Camera2D& cam = Application::camera;
    if(InputManager::GetKey(GLFW_KEY_W))
    {
        cam.position.y += deltaTime * cameraSpeed;
    }
    if(InputManager::GetKey(GLFW_KEY_S))
    {
        cam.position.y -= deltaTime * cameraSpeed;
    }
    if(InputManager::GetKey(GLFW_KEY_A))
    {
        cam.position.x -= deltaTime * cameraSpeed;
    }
    if(InputManager::GetKey(GLFW_KEY_D))
    {
        cam.position.x += deltaTime * cameraSpeed;
    }
    MouseScrollEvent scrollEvent = InputManager::GetMouseScroll();
    if(scrollEvent.scrolled)
    {
        cam.Zoom(scrollEvent.amount);
    }
}

void TestBatching::Render(Renderer2D& renderer)
{
    m_Shader->Bind();
    m_Shader->SetMat4("u_View", Application::camera.GetViewMatrix());
    m_Shader->SetMat4("u_Projection", Application::camera.GetProjectionMatrix());
    
    std::array<Vertex, 108> vertices;
    Vertex* buffer = vertices.data();

    unsigned int indexCount = 0;
    for(int y = 0; y < 5; y++)
    {
        for(int x = 0; x < 5; x++)
        {
            buffer = CreateQuad(buffer, x*50, y*50, glm::vec3((x + y) % 2));
            indexCount += 6;
        }
    }

    buffer = CreateQuad(buffer, m_Position1.x, m_Position1.y, glm::vec3(1.0f, 1.0f, 1.0f));
    indexCount += 6;
    buffer = CreateQuad(buffer, m_Position1.x + 100, m_Position1.y, glm::vec3(1.0f, 1.0f, 1.0f));
    indexCount += 6;

    m_VBO->Bind();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()));

    m_VAO->Bind();
    m_EBO->Bind();

    GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
}

void TestBatching::ImGuiRender()
{
    ImGui::SliderFloat2("Position", &m_Position1.x, -500.0f, 500.0f);
}

Vertex* CreateQuad(Vertex* target, float x, float y, glm::vec3 color, float size)
{
    target->position = {x, y};
    target->texCoords = {0.0f, 0.0f};
    target->color = color;
    target++;

    target->position = {x + size, y};
    target->texCoords = {1.0f, 0.0f};
    target->color = color;
    target++;

    target->position = {x + size, y + size};
    target->texCoords = {1.0f, 1.0f};
    target->color = color;
    target++;

    target->position = {x, y + size};
    target->texCoords = {0.0f, 1.0f};
    target->color = color;
    target++;

    return target;
}

}


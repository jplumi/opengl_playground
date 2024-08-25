#include "Renderer2D.hpp"
#include "Camera2D.hpp"
#include "IndexBuffer.hpp"
#include "OpenGLDebug.hpp"
#include "Shader.hpp"

Renderer2D::Renderer2D(Camera2D& camera)
    : m_Camera(camera), m_QuadVAO(0), m_QuadVBO(0), m_QuadEBO(0)
{
    float vertices[] = {
        50.0f, 50.0f,   1.0f, 1.0f, 
        50.0f, -50.0f,  1.0f, 0.0f,
        -50.0f, -50.0f, 0.0f, 0.0f,
        -50.0f, 50.0f,  0.0f, 1.0f,
    };
    
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    m_QuadVAO = new VertexArray();

    m_QuadVBO = new VertexBuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    m_QuadEBO = new IndexBuffer(indices, sizeof(indices));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);
    layout.Push(GL_FLOAT, 2);

    m_QuadVAO->AddBuffer(*m_QuadVBO, layout);
}

Renderer2D::~Renderer2D()
{
    delete m_QuadVAO;
    delete m_QuadVBO;
    delete m_QuadEBO;
}

void Renderer2D::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    shader.Bind();
    shader.SetMat4("u_Projection", m_Camera.GetProjectionMatrix());
    shader.SetMat4("u_View", m_Camera.GetViewMatrix());
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer2D::Draw(const Texture& texture, const Shader& shader, glm::vec2 position,
                      glm::vec2 scale, glm::vec3 color)
{

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0));

    shader.Bind();
    shader.SetVec3("u_Color", color.x, color.y, color.z);
    shader.SetMat4("u_Projection", m_Camera.GetProjectionMatrix());
    shader.SetMat4("u_View", m_Camera.GetViewMatrix());
    shader.SetMat4("u_Model", model);

    m_QuadVAO->Bind();
    m_QuadEBO->Bind();

    texture.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, m_QuadEBO->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer2D::Clear()
{
    GLCall(glClearColor(0.3f, 0.5f, 0.6f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}


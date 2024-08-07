#include "Renderer.hpp"
#include "OpenGLDebug.hpp"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    GLCall(glClearColor(0.3f, 0.5f, 0.6f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}


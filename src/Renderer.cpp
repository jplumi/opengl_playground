#include "Renderer.hpp"
#include <iostream>

void Renderer::GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

void Renderer::GLCheckError()
{
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error]: " << error << '\n';
    }
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(0.3f, 0.5f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


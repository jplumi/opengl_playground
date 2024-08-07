#include "Renderer.hpp"
#include <iostream>

void Renderer::GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool Renderer::GLLogCall(const char* function, const char* file, int line)
{
    if(GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error]: (" << error << "): " << function << " at " << file << ":" << line << '\n';
        return false;
    }
    return true;
}

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


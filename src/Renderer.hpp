#pragma once

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"


class Renderer
{
public:
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    static void Clear();

    static void GLClearError();
    static bool GLLogCall(const char* function, const char* file, int line);
};

#define GLCall(x) Renderer::GLClearError(); x; Renderer::GLLogCall(#x, __FILE__, __LINE__)


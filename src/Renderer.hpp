#pragma once

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;

    static void GLClearError();
    static void GLCheckError();
};


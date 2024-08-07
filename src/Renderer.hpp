#pragma once

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"


class Renderer
{
public:
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    static void Clear();
};



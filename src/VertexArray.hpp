#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "glm/glm.hpp"

struct Vertex
{
    glm::vec2 position;
    glm::vec2 texCoords;
};

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void Unbind() const;
    
    static std::array<Vertex, 4> CreateQuad(float x, float y);

private:
    unsigned int m_ID;
};


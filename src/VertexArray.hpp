#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "glm/glm.hpp"

struct Vertex
{
    glm::vec2 position;
    glm::vec2 texCoords;
    glm::vec3 color;
};

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void Unbind() const;
    
    static std::array<Vertex, 4> CreateQuad(float x, float y, glm::vec3 color, float size = 50.0f);

private:
    unsigned int m_ID;
};


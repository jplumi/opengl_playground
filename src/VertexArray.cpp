#include "VertexArray.hpp"

#include "VertexBufferLayout.hpp"
#include "glad/glad.h"
#include <vector>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
    glBindVertexArray(m_ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    vb.Bind();
    const std::vector<VertexBufferElement>& elements = layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        VertexBufferElement element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalized,
                              layout.GetStride(),
                              (const void*)offset);
        glEnableVertexAttribArray(i);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_ID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

std::array<Vertex, 4> VertexArray::CreateQuad(float x, float y)
{
    Vertex v0;
    v0.position = {x, y};
    v0.texCoords = {1.0f, 1.0f};

    Vertex v1;
    v1.position = {x, -y};
    v1.texCoords = {1.0f, 0.0f};

    Vertex v2;
    v2.position = {-x, -y};
    v2.texCoords = {0.0f, 0.0f};

    Vertex v3;
    v3.position = {-x, y};
    v3.texCoords = {0.0f, 1.0f};

    return { v0, v1, v2, v3 };
}


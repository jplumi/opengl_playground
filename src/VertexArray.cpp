#include "VertexArray.hpp"

#include "Renderer.hpp"
#include "VertexBufferLayout.hpp"
#include "glad/glad.h"
#include <vector>

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_ID));
    GLCall(glBindVertexArray(m_ID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_ID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    vb.Bind();
    const std::vector<VertexBufferElement>& elements = layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        VertexBufferElement element = elements[i];
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
                              layout.GetStride(),
                              (const void*)offset));
        GLCall(glEnableVertexAttribArray(i));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_ID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

std::array<Vertex, 4> VertexArray::CreateQuad(float x, float y, glm::vec3 color, float size)
{
    Vertex v0;
    v0.position = {x, y};
    v0.texCoords = {1.0f, 1.0f};
    v0.color = color;

    Vertex v1;
    v1.position = {x + size, y};
    v1.texCoords = {1.0f, 0.0f};
    v1.color = color;

    Vertex v2;
    v2.position = {x + size, y + size};
    v2.texCoords = {0.0f, 0.0f};
    v2.color = color;

    Vertex v3;
    v3.position = {x, y + size};
    v3.texCoords = {0.0f, 1.0f};
    v3.color = color;

    return { v0, v1, v2, v3 };
}


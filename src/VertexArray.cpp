#include "VertexArray.hpp"

#include "OpenGLDebug.hpp"
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



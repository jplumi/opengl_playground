#pragma once

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size, unsigned int drawType);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
private:
    unsigned int m_RendererID;
};


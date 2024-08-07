#include "Texture.hpp"
#include "OpenGLDebug.hpp"
#include "Shader.hpp"

Texture::Texture() {}

Texture::Texture(unsigned int texId, int width, int height, int bpp)
    : m_ID(texId), 
    m_Width(width), m_Height(height), m_BPP(bpp) {}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_ID));
}

void Texture::SetData(unsigned int texId, int width, int height, int bpp)
{
    m_ID = texId;
    m_Width = width;
    m_Height = height;
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}


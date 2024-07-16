#include "Texture.hpp"
#include "Shader.hpp"

Texture::Texture() {}

Texture::Texture(unsigned int texId, int width, int height, int bpp)
    : m_ID(texId), 
    m_Width(width), m_Height(height), m_BPP(bpp) {}

Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}


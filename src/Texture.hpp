#pragma once

class Texture
{
public:
    Texture();
    Texture(unsigned int texId, int width, int height, int bpp);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }

private:
    unsigned int m_ID;
    int m_Width, m_Height, m_BPP;
};


#include "Texture2D.h"
#include <vector>

Texture2D::Texture2D()
{
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture2D::~Texture2D()
{
}

unsigned int Texture2D::GetID()
{
    return m_textureID;
}

void Texture2D::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

bool Texture2D::setImage(Image2D& image)
{
    if (!image.GetData().empty())
    {
        GLenum format;
        if (image.GetChannels() == 1)
            format = GL_RED;
        else if (image.GetChannels() == 3)
            format = GL_RGB;
        else if (image.GetChannels() == 4)
            format = GL_RGBA;
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, image.GetWidth(), image.GetHeight(), 0, format, GL_UNSIGNED_BYTE, image.GetData().data());
        glGenerateMipmap(GL_TEXTURE_2D);
        return true;
    }
    return false;
}

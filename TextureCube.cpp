#include "TextureCube.h"

TextureCube::TextureCube()
{
    glGenTextures(1, &_textureID);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

TextureCube::TextureCube(std::array<Image2D, 6> images)
    :TextureCube()
{
    this->setImage(images);
}

TextureCube::TextureCube(const TextureCube & rhs)
    :_textureID(rhs._textureID)
{
}

TextureCube & TextureCube::operator=(const TextureCube & rhs)
{
    _textureID = rhs._textureID;
    return *this;
}

TextureCube::~TextureCube()
{
}

void TextureCube::setImage(std::array<Image2D, 6> images)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
    for (int i = 0; i < images.size(); ++i)
    {
        if (!images[i].GetData().empty())
        {
            GLenum format;
            if (images[i].GetChannels() == 1)
                format = GL_RED;
            else if (images[i].GetChannels() == 3)
                format = GL_RGB;
            else if (images[i].GetChannels() == 4)
                format = GL_RGBA;
           
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, format, images[i].GetWidth(), images[i].GetHeight(), 0, format, GL_UNSIGNED_BYTE, images[i].GetData().data()
            );
           // glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
}

void TextureCube::bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
}

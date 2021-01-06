#include "Texture2D.h"
#include <vector>
#include <iostream>

Texture2D::Texture2D()
{
    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture2D::Texture2D(Image2D& image)
    :Texture2D()
{
    setImage(image);
}

Texture2D::~Texture2D()
{
}

Texture2D::Texture2D(const Texture2D & rhs)
    :_textureID(rhs._textureID)
    ,_textureType(rhs._textureType)
    ,_image(rhs._image)
{
}

Texture2D & Texture2D::operator=(const Texture2D & rhs)
{
    _textureID = rhs._textureID;
    _textureType = rhs._textureType;
    _image = rhs._image;
    return *this;
}

unsigned int Texture2D::getID()
{
    return _textureID;
}

void Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

bool Texture2D::setImage(Image2D& image)
{
    _image = image;
    if (!image.GetData().empty())
    {
        GLenum format;
        if (image.GetChannels() == 1)
            format = GL_RED;
        else if (image.GetChannels() == 3)
            format = GL_RGB;
        else if (image.GetChannels() == 4)
            format = GL_RGBA;
        glBindTexture(GL_TEXTURE_2D, _textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, image.GetWidth(), image.GetHeight(), 0, format, GL_UNSIGNED_BYTE, image.GetData().data());
        glGenerateMipmap(GL_TEXTURE_2D);
        return true;
    }

    std::cout << "Texture2D::setImage falied" << std::endl;
    return false;
}

Texture2D::TextureType Texture2D::getType()
{
    return _textureType;
}

void Texture2D::setType(TextureType type)
{
    _textureType = type;
}

std::string Texture2D::getImagePath()
{
    return _image.getPath();
}

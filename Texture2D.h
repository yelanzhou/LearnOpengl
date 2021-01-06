#pragma once

#include "Image2D.h"
#include <glad/glad.h>

class Texture2D
{
public:
    enum class TextureType
    {
        Diffuse,
        Specular,
        Normal,
        Height,
    };


public:
    Texture2D();
    Texture2D(Image2D& image);
    Texture2D(const Texture2D& rhs);
    
    Texture2D& operator=(const Texture2D& rhs);

    ~Texture2D();
    

    unsigned int getID();
    void bind();
    bool setImage(Image2D& image);
    TextureType getType();
    void setType(TextureType type);
    std::string getImagePath();

private:

    unsigned int  _textureID; 
    TextureType   _textureType = TextureType::Diffuse;
    Image2D       _image;

};
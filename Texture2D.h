#pragma once

#include "Image2D.h"
#include <glad/glad.h>

class Texture2D
{
public:
    Texture2D();
    ~Texture2D();
    unsigned int GetID();
    void Bind();
    bool setImage(Image2D& image);

private:

    unsigned int m_textureID;

};
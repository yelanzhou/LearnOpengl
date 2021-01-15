#pragma once

#include "glad\glad.h"
#include "Image2D.h"

#include <vector>
#include <array>

class TextureCube
{
private:

    unsigned int _textureID;
    //std::array<Image2D, 6> _images;


public:
    TextureCube();
    TextureCube(std::array<Image2D, 6> images);
    TextureCube(const TextureCube& rhs);
    TextureCube& operator=(const TextureCube& rhs);

    ~TextureCube();

    void setImage(std::array<Image2D, 6> images);
    void bind();


};
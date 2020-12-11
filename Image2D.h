#pragma once
#include "stb_image.h"

#include <string>
#include <vector>

class Image2D
{
public:
    Image2D(std::string file);
    Image2D();
    Image2D(const Image2D& rhs);

    int GetHeight();
    int GetWidth();
    int GetChannels();
    const std::vector<unsigned char>& GetData();

private:

    int m_height;
    int m_width;
    int m_channels;
    std::vector<unsigned char> m_data;

};
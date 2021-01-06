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

    Image2D& operator=(const Image2D& rhs);

    int GetHeight();
    int GetWidth();
    int GetChannels();
    const std::vector<unsigned char>& GetData();

    std::string getPath();

private:

    std::string _path;
    int _height;
    int _width;
    int _channels;
    std::vector<unsigned char> _data;

};
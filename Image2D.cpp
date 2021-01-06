#include "Image2D.h"

Image2D::Image2D(std::string file)
    :_path(file)
{
  unsigned char* data = stbi_load(file.c_str(), &_width, &_height, &_channels, 0);

  _data.resize(_width*_height*_channels);
  std::copy(data, data + _data.size(), _data.data());
   
  stbi_image_free(data);
}

Image2D::Image2D()
{
   
}

Image2D::Image2D(const Image2D & rhs)
    :_width(rhs._width)
    ,_height(rhs._height)
    ,_channels(rhs._channels)
    ,_data(rhs._data)
    ,_path(rhs._path)
{
}

Image2D & Image2D::operator=(const Image2D & rhs)
{
    _width = rhs._width;
    _height = rhs._height;
    _channels = rhs._channels;
    _data = rhs._data;
    _path = rhs._path;
    return *this;
}

int Image2D::GetHeight()
{
    return _height;
}

int Image2D::GetWidth()
{
    return _width;
}

int Image2D::GetChannels()
{
    return _channels;
}

const std::vector<unsigned char>& Image2D::GetData()
{
    return _data;
}

std::string Image2D::getPath()
{
    return _path;
}

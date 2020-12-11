#include "Image2D.h"

Image2D::Image2D(std::string file)
{
  unsigned char* data = stbi_load(file.c_str(), &m_width, &m_height, &m_channels, 0);

  m_data.resize(m_width*m_height*m_channels);
  std::copy(data, data + m_data.size(), m_data.data());
   
  stbi_image_free(data);
}

Image2D::Image2D()
{
   
}

Image2D::Image2D(const Image2D & rhs)
    :m_width(rhs.m_width)
    ,m_height(rhs.m_height)
    ,m_channels(rhs.m_channels)
    ,m_data(rhs.m_data)
{
}

int Image2D::GetHeight()
{
    return m_height;
}

int Image2D::GetWidth()
{
    return m_width;
}

int Image2D::GetChannels()
{
    return m_channels;
}

const std::vector<unsigned char>& Image2D::GetData()
{
    return m_data;
}

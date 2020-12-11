#include "ImageReader.h"

ImageReader::ImageReader(std::string file)
{
   m_data = stbi_load(file.c_str(), &m_width, &m_height, &m_channels, 0);
}

ImageReader::ImageReader()
{
    stbi_image_free(m_data);
}

int ImageReader::GetHeight()
{
    return m_height;
}

int ImageReader::GetWidth()
{
    return m_width;
}

int ImageReader::GetChannels()
{
    return m_channels;
}

unsigned char * ImageReader::Data()
{
    return m_data;
}

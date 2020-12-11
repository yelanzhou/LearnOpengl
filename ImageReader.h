#pragma once
#include "stb_image.h"

#include <string>

class ImageReader
{
public:
    ImageReader(std::string file);
    ImageReader();

    int GetHeight();
    int GetWidth();
    int GetChannels();
    unsigned char* Data();

private:

    int m_height;
    int m_width;
    int m_channels;
    unsigned char* m_data = nullptr;



};
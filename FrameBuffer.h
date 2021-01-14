#pragma once

#include <glad/glad.h>

class FrameBuffer
{


public:
    FrameBuffer(int width,int height);
    FrameBuffer();
    ~FrameBuffer();

    void bind();
    void setSize(int width, int height);
    void bindColorTexture();


private:
    unsigned int _fbo;
    unsigned int _textureColorBuffer;
    unsigned int _renderDepthBuffer;

    int _width = 800;
    int _height = 600;
};
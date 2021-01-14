#include "FrameBuffer.h"
#include <iostream>

FrameBuffer::FrameBuffer()
{
    glGenFramebuffers(1, &_fbo);
    glGenTextures(1, &_textureColorBuffer);
    glGenRenderbuffers(1, &_renderDepthBuffer);
    setSize(_width, _height);
}

FrameBuffer::FrameBuffer(int width, int height)
    :_width(width)
    ,_height(height)
{
    glGenFramebuffers(1, &_fbo);
    glGenTextures(1, &_textureColorBuffer);
    glGenRenderbuffers(1, &_renderDepthBuffer);
    setSize(_width, _height);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &_fbo);
}

void FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

void FrameBuffer::setSize(int width, int height)
{
    bind();
    glBindTexture(GL_TEXTURE_2D, _textureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureColorBuffer, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, _renderDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderDepthBuffer); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bindColorTexture()
{
    glBindTexture(GL_TEXTURE_2D, _textureColorBuffer);
}

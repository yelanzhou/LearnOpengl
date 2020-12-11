#pragma once

#include <glad/glad.h>
#include <string>
class Shader
{
public:
    Shader(std::string vertexShaderFile, std::string fragShaderFile);
    ~Shader();
    void Use();
    void setFloat(const char* name,float value);
    void setInt(const char* name, int value);

private:
    unsigned int m_id;
};


#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(std::string vertexShaderFile, std::string fragShaderFile)
{
    std::ifstream vertexShaderFileStream;
    std::ifstream fragShaderFileStream;

    vertexShaderFileStream.open(vertexShaderFile);
    fragShaderFileStream.open(fragShaderFile);

    std::stringstream vertexShaderStringStream;
    std::stringstream fragShaderStringStream;

    vertexShaderStringStream << vertexShaderFileStream.rdbuf();
    fragShaderStringStream << fragShaderFileStream.rdbuf();

    vertexShaderFileStream.close();
    fragShaderFileStream.close();

    std::string vertexShaderCode = vertexShaderStringStream.str();
    std::string fragShaderCode = fragShaderStringStream.str();
    const char* vCode = vertexShaderCode.c_str();
    const char* fCode = fragShaderCode.c_str();

    int success = 0;
    char log[512];
    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1,&vCode, NULL);
    glCompileShader(vShader);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vShader, 512, NULL, log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
    }

    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fCode, NULL);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fShader, 512, NULL, log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vShader);
    glAttachShader(m_id, fShader);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 1024, NULL, log);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: \n" << log << std::endl;
    }
    
    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

Shader::~Shader()
{
}

void Shader::Use()
{
    glUseProgram(m_id);
}

void Shader::setFloat(const char* name,float value)
{
    glUniform1f(glGetUniformLocation(m_id, name), value);
}

void Shader::setInt(const char * name, int value)
{
    glUniform1i(glGetUniformLocation(m_id, name), value);
}

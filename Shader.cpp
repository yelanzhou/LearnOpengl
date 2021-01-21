#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(std::string vertexShaderFile, std::string fragShaderFile,std::string geoShaderFile)
{

    auto vShader = createShader(vertexShaderFile, GL_VERTEX_SHADER);
    auto fShader = createShader(fragShaderFile, GL_FRAGMENT_SHADER);

    unsigned gShader = 0;
    if (!geoShaderFile.empty())
    {
        createShader(geoShaderFile, GL_GEOMETRY_SHADER);
    }




    int success = 0;
    char log[512];
    m_id = glCreateProgram();
    glAttachShader(m_id, vShader);
    glAttachShader(m_id, fShader);
    if (!geoShaderFile.empty())
    {
        glAttachShader(m_id, gShader);
    }
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

void Shader::setInt(const char * name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name), value);
}

void Shader::setMarix4f(const char * name, glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_id,name), 1,GL_FALSE,glm::value_ptr(matrix));
}

void Shader::setVec3(const char * name, glm::vec3 vec)
{
    glUniform3fv(glGetUniformLocation(m_id, name), 1, &vec[0]);
}

unsigned int Shader::getProgramID()
{
    return m_id;
}

unsigned int Shader::createShader(std::string path, unsigned int type)
{
    std::ifstream shaderSteam;
    shaderSteam.open(path);

    std::stringstream shaderStringStream;
    shaderStringStream << shaderSteam.rdbuf();

    shaderSteam.close();
    
    std::string shaderString = shaderStringStream.str();
    const char* shaderCode = shaderString.c_str();

    int success = 0;
    char log[512];
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, log);
        std::cout << path << "  error" << log << std::endl;
    }


    return shader;
}

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
class Shader
{
public:
    Shader(std::string vertexShaderFile, std::string fragShaderFile,std::string geometryShaderFile = "");
    ~Shader();
    void Use();
    void setFloat(const char* name,float value);
    void setInt(const char* name, int value)const;
    void setMarix4f(const char* name, glm::mat4 matrix);
    void setVec3(const char* name, glm::vec3 vec);

    unsigned int getProgramID();

private:

    unsigned int createShader(std::string Path,unsigned int type);

    unsigned int m_id;
};


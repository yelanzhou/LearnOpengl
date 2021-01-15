#pragma once

#include "Shader.h"
#include <string>



class SkyBox
{
public:
    SkyBox(std::string path);
    ~SkyBox();

    void draw(Shader& shader);


private:
    unsigned int _VAO;
    unsigned int _VBO;
    unsigned int _EBO;



};
#pragma once

#include "Shader.h"
#include "TextureCube.h"
#include <string>
#include <memory>



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

    std::shared_ptr<TextureCube> _texture;



};
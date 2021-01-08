#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <memory>

class CubeModel
{

public:
    CubeModel(std::string diffuse,std::string specular,float a = 1.0,float b = 1.0,float c = 1.0);
    ~CubeModel();

    void draw(Shader& shader);


private:

    std::shared_ptr<Mesh> _mesh;


};

#pragma once

#include "Mesh.h"
#include "Shader.h"

#include <memory>
class PlaneModel
{
public:

    PlaneModel(std::string diffuse, std::string specular);
    ~PlaneModel();


    void draw(Shader& shader);



private:
    std::shared_ptr<Mesh> _mesh;

};
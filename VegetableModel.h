#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <memory>


class  VegetableModel
{
public:
    VegetableModel(std::string diffuse, std::string specular);
    ~VegetableModel();

    void draw(Shader& shader);

private:


    std::shared_ptr<Mesh> _mesh;





};
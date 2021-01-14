#pragma once

#include "Mesh.h"
#include "Shader.h"
#include <memory>

//主要用来后处理，所以没有diffuse和specular，直接使用上一个阶段的渲染输出
class QuadModel
{
public:

    QuadModel();
    ~QuadModel();
    void draw(Shader& shader);
private:

    std::shared_ptr<Mesh> _mesh;
    
};
#pragma once

#include "Mesh.h"
#include "Shader.h"
#include <memory>

//��Ҫ������������û��diffuse��specular��ֱ��ʹ����һ���׶ε���Ⱦ���
class QuadModel
{
public:

    QuadModel();
    ~QuadModel();
    void draw(Shader& shader);
private:

    std::shared_ptr<Mesh> _mesh;
    
};
#pragma once
#include "Texture2D.h"
#include "Shader.h"
#include <glm/glm.hpp>

#include <vector>


struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
    glm::vec3 tangent;
    glm::vec3 bitTangent;
};

class Mesh
{
public:

    Mesh(const std::vector<Vertex>& vertexs, const std::vector<unsigned int>& indexes, const std::vector<std::shared_ptr<Texture2D>>& textures);
    ~Mesh();
    
    void draw(const Shader& shader);


private:

    void setUpMesh();

    std::vector<Vertex> _vertexs;
    std::vector<unsigned int> _indexes;
    std::vector<std::shared_ptr<Texture2D>>    _textures;

    unsigned int _VAO;
    unsigned int _VBO;
    unsigned int _EBO;

};
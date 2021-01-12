#include "VegetableModel.h"
float transparentVertices[] = {
    // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
    0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
    1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};


VegetableModel::VegetableModel(std::string diffuse, std::string specular)
{
    Vertex vertex;
    std::vector<Vertex> vertexes;
    for (int i = 0; i < 6; ++i)
    {
        vertex.position = glm::vec3(transparentVertices[5 * i], transparentVertices[5 * i + 1], transparentVertices[5 * i + 2]);
        //vertex.normal = glm::vec3(planeVertices[8 * i + 3], planeVertices[8 * i + 4], planeVertices[8 * i + 5]);
        vertex.texCoord = glm::vec2(transparentVertices[5 * i + 3], transparentVertices[5 * i + 4]);
        vertexes.push_back(vertex);
    }

    std::vector<unsigned int>  indices =
    {
        0,1,2,
        3,4,5
    };


    Image2D diffImage(diffuse);
    auto diffTex = std::make_shared<Texture2D>(diffImage);

    Image2D specularImage(specular);
    auto specTex = std::make_shared<Texture2D>(specularImage);
    specTex->setType(Texture2D::TextureType::Specular);

    std::vector<std::shared_ptr<Texture2D>> textures{ diffTex ,specTex };

    _mesh = std::make_shared<Mesh>(vertexes, indices, textures);
}

VegetableModel::~VegetableModel()
{
}

void VegetableModel::draw(Shader & shader)
{
    _mesh->draw(shader);
}

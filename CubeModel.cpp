#include "CubeModel.h"
#include "Image2D.h"
#include "Texture2D.h"



float vertices[] = {

    // 0,1,2; 2,3,0
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

     // 4,5,6;6;7;4
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

    //8,9,10;10,11,8
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,


    //12.13.14;14,15,12
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

     //16,17,18;18,19,16
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

    //20,21,22,22,23,20
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

};

CubeModel::CubeModel(std::string diffuse, std::string specular,float a,float b,float c)
{
    Vertex vertex;
    std::vector<Vertex> vertexes;
    for (int i = 0; i < 24; ++i)
    {
        vertex.position = glm::vec3(vertices[8 * i], vertices[8 * i+1], vertices[8 * i+2]);
        vertex.normal = glm::vec3(vertices[8 * i+3], vertices[8 * i + 4], vertices[8 * i + 5]);
        vertex.texCoord = glm::vec2(vertices[8 * i + 6], vertices[8 * i + 7]);
        vertexes.push_back(vertex);

    }

    std::vector<unsigned int> indices =
    {
         0,1,2, 2,3,0,
         4,5,6, 6,7,4,
         8,9,10, 10,11,8,
         12,13,14, 14,15,12,
         16,17,18, 18,19,16,
         20,21,22, 22,23,20,
    };

    Image2D diffImage(diffuse);
    auto diffTex = std::make_shared<Texture2D>(diffImage);

    Image2D specularImage(specular);
    auto specTex = std::make_shared<Texture2D>(specularImage);
    specTex->setType(Texture2D::TextureType::Specular);

    std::vector<std::shared_ptr<Texture2D>> textures{ diffTex ,specTex };

    _mesh = std::make_shared<Mesh>(vertexes, indices, textures);



}

CubeModel::~CubeModel()
{
}

void CubeModel::draw(Shader& shader)
{
    _mesh->draw(shader);
}

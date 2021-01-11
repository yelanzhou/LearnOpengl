#include "PlaneModel.h"


float planeVertices[] = {
    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
     5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};

PlaneModel::PlaneModel(std::string diffuse, std::string specular)
{
    Vertex vertex;
    std::vector<Vertex> vertexes;
    for (int i = 0; i < 6; ++i)
    {
        vertex.position = glm::vec3(planeVertices[ 5* i], planeVertices[5 * i + 1], planeVertices[5 * i + 2]);
        //vertex.normal = glm::vec3(planeVertices[8 * i + 3], planeVertices[8 * i + 4], planeVertices[8 * i + 5]);
        vertex.texCoord = glm::vec2(planeVertices[5* i + 3], planeVertices[5 * i + 4]);
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

PlaneModel::~PlaneModel()
{
}

void PlaneModel::draw(Shader & shader)
{
    _mesh->draw(shader);
}

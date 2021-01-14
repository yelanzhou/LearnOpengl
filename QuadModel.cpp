#include "QuadModel.h"

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

QuadModel::QuadModel()
{
    Vertex vertex;
    std::vector<Vertex> vertexes;
    for (int i = 0; i < 6; ++i)
    {
        vertex.position = glm::vec3(quadVertices[4 * i], quadVertices[4 * i + 1], 0.0);   
        vertex.texCoord = glm::vec2(quadVertices[4 * i + 2], quadVertices[4 * i + 3]);
        vertexes.push_back(vertex);
    }

    std::vector<unsigned int> indices =
    {
         0,1,2, 3,4,5,

    };

    std::vector<std::shared_ptr<Texture2D>> textures;

    _mesh = std::make_shared<Mesh>(vertexes, indices, textures);
}

QuadModel::~QuadModel()
{
}

void QuadModel::draw(Shader & shader)
{
    _mesh->draw(shader);
}

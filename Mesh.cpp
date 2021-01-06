#include "Mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::Mesh(const std::vector<Vertex>& vertexs, const std::vector<unsigned int>& indexes, const std::vector<std::shared_ptr<Texture2D>>& textures)
    :_vertexs(vertexs)
    ,_indexes(indexes)
    ,_textures(textures)
{
    setUpMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1,&_VAO);
    glDeleteBuffers(1, &_EBO);
    glDeleteBuffers(1, &_VBO);
}

void Mesh::draw(const Shader & shader)
{
    unsigned int diffuseCount = 1;
    unsigned int specularCount = 1;
    unsigned int normalCount = 1;
    unsigned int heightCount = 1;

    for (int i  = 0; i < _textures.size(); ++i)
    {
        std::string name("texture_");
        switch (_textures[i]->getType())
        {

        case Texture2D::TextureType::Diffuse:
        {
            name = name + "diffuse" + std::to_string(diffuseCount++);
            break;
        }
        case Texture2D::TextureType::Specular:
        {
            name = name + "specular" + std::to_string(normalCount++);
            break;
        }
        case Texture2D::TextureType::Normal:
        {
            name = name + "normal" + std::to_string(normalCount++);
            break;
        }
        case Texture2D::TextureType::Height:
        {            
            name = name + "height" + std::to_string(heightCount++);
            break;
        }
        }

        glActiveTexture(GL_TEXTURE0 + i);
        shader.setInt(name.c_str(),i);
        glBindTexture(GL_TEXTURE_2D, _textures[i]->getID());

    }

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indexes.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);

}

void Mesh::setUpMesh()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBindVertexArray(0);
    glBufferData(GL_ARRAY_BUFFER, _vertexs.size() * sizeof(Vertex), &_vertexs[0], GL_STATIC_DRAW);
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexes.size() * sizeof(unsigned int),&_indexes[0], GL_STATIC_DRAW);

    // 顶点位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // 顶点法线
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // 顶点纹理坐标
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitTangent));

    glBindVertexArray(0);


}

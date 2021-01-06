#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "Texture2D.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <memory>

class Model
{
public:
    Model(std::string path);
    ~Model();

    void draw(const Shader& shader);

private:

    void LoadModel(std::string path);

    void processNode(aiNode *node, const aiScene *scene);
    std::shared_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<std::shared_ptr<Texture2D>> loadMaterialTextures(aiMaterial *mat, aiTextureType type);

    Texture2D::TextureType connvertTextureType(aiTextureType type);

    std::vector<std::shared_ptr<Mesh>>               _meshs;
    std::vector<std::shared_ptr<Texture2D>>          _textures;
    std::string                                      _directory;
    

};
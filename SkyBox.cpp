#include "SkyBox.h"
#include "Image2D.h"
#include "TextureCube.h"



float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

std::vector<std::string> names = {"/right.jpg","/left.jpg","/top.jpg","/bottom.jpg","/front.jpg","/back.jpg"};


SkyBox::SkyBox(std::string path)
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
   // glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    // ∂•µ„Œª÷√
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glBindVertexArray(0);

    std::array<Image2D, 6> images;
    for (int i = 0; i < 6; ++i)
    {
        std::string file = path + names[i];
        images[i] = Image2D(file);
    }

    _texture = std::make_shared<TextureCube>();
    _texture->setImage(images);

}

SkyBox::~SkyBox()
{
    glDeleteBuffers(1,&_VBO);
    glDeleteVertexArrays(1,&_VAO);
}

void SkyBox::draw(Shader & shader)
{
    glBindVertexArray(_VAO);
    glActiveTexture(GL_TEXTURE0);
    _texture->bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

}

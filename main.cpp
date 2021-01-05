//#include <glad/glad.h>
//#include <GLFW/glfw3.h>


#include "initGL.h"
#include "Shader.h"
#include "Image2D.h"
#include "Texture2D.h"
#include "Light.h"

#include <glm/gtc/matrix_transform.hpp>

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
// world space positions of our cubes
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f) };

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
};

int main()
{
    GLFWwindow* window;
    if (!initGL(800, 600, window))
    {
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    Shader shader("..\\..\\shader_source\\multi_light.vert", "..\\..\\shader_source\\multi_light.frag");

    Image2D containerImage("..\\..\\textures\\container2.png");  
    Texture2D texture0;
    texture0.setImage(containerImage);

    Image2D specularImage("..\\..\\textures\\container2_specular.png");
    Texture2D texture1;
    texture1.setImage(specularImage);

    
    Light dirLight;
    dirLight.setLightType(Light::LightType::Direction);
    dirLight.setDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
    dirLight.setAmbientColor(glm::vec4( 0.05f, 0.05f, 0.05f,1.0f));
    dirLight.setDiffuseColor(glm::vec4( 0.4f, 0.4f, 0.4f,1.0f));
    dirLight.setSpecularColor(glm::vec4(0.5f, 0.5f, 0.5f,1.0f));
   
    Light pointLights[4];
    for (int i = 0; i < 4; ++i)
    {
        pointLights[i].setLightType(Light::LightType::Point);
        pointLights->setPosition(pointLightPositions[i]);
    }

    unsigned int VBO;
    glGenBuffers(1, &VBO);

  /*  unsigned int EBO;
    glGenBuffers(1, &EBO);
  */
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    shader.Use();
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 1);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);


        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        texture0.Bind();

        glActiveTexture(GL_TEXTURE1);
        texture1.Bind();


        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(g_camera.GetZoom()), (float)800 / (float)600, 0.1f, 100.0f);
        shader.setMarix4f("projection", projection);

        // camera/view transformation
        glm::mat4 view = g_camera.GetVieMatrix();
        shader.setMarix4f("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        shader.setMarix4f("model", model);

    
       
        shader.setVec3("viewPos", g_camera.GetPosition());

        shader.setVec3("dirLight.ambient", dirLight.getAmbientColor());
        shader.setVec3("dirLight.diffuse", dirLight.getDiffuseColor());
        shader.setVec3("dirLight.specular", dirLight.getSpecularColor());
        shader.setVec3("dirLight.direction", dirLight.getDirection());


        for (int i = 0; i < 4; ++i)
        {
            std::string ambient = std::string("pointLights[") + std::to_string(i) + std::string("].ambient");
            std::string diffuse = std::string("pointLights[") + std::to_string(i) + std::string("].diffuse");
            std::string specular = std::string("pointLights[") + std::to_string(i) + std::string("].specular");
            std::string position = std::string("pointLights[") + std::to_string(i) + std::string("].position");
            std::string constant = std::string("pointLights[") + std::to_string(i) + std::string("].constant");
            std::string linear = std::string("pointLights[") + std::to_string(i) + std::string("].linear");
            std::string quadratic = std::string("pointLights[") + std::to_string(i) + std::string("].quadratic");
            shader.setVec3(ambient.c_str(), pointLights[i].getAmbientColor());
            shader.setVec3(diffuse.c_str(), pointLights[i].getDiffuseColor());
            shader.setVec3(specular.c_str(), pointLights[i].getSpecularColor());
            shader.setVec3(position.c_str(), pointLights[i].getPosition());
            shader.setFloat(constant.c_str(), pointLights[i].getAttenuationConstant());
            shader.setFloat(linear.c_str(), pointLights[i].getAttenuationLinear());
            shader.setFloat(quadratic.c_str(), pointLights[i].getAttenuationQuadartic());
        }

    
        shader.setFloat("material.shininess", 32.0f); 
        shader.Use();

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
       
        for (int i = 0; i < 10; ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMarix4f("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------

    //glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VAO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
    return 0;
}

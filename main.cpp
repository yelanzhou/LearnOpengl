//#include <glad/glad.h>
//#include <GLFW/glfw3.h>


#include "initGL.h"
#include "Shader.h"
#include "Image2D.h"
#include "Texture2D.h"
#include "Light.h"
#include "Model.h"
#include "CubeModel.h"
#include "PlaneModel.h"
#include "VegetableModel.h"
#include "FrameBuffer.h"
#include "QuadModel.h"
#include "SkyBox.h"


#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <map>

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
// world space positions of our cubes

int depthWidth = 1024;
int depthHeight = 1024;


float planeVertices1[] = {
    // positions            // normals         // texcoords
     10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
    -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
    -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

     10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
    -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
     10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
};

glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
float light_near = 1.0;
float light_far = 7.5;

int main()
{
    GLFWwindow* window;
    if (!initGL(800, 600, window))
    {
        return -1;
    }

    auto lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, light_near, light_far);
    auto lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    auto lightMatrix = lightProjection * lightView;



    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_FRAMEBUFFER_SRGB);


    unsigned int VAO;
    unsigned int VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices1), &planeVertices1, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    Image2D image("../../textures/Wood.png");
    Texture2D texture;
    texture.setImage(image);

    Shader depthShader("../../shader_source/depth.vert", "../../shader_source/depth.frag");
    depthShader.Use();
    depthShader.setMarix4f("lightMatrix", lightMatrix);


    Shader showDepthShader("../../shader_source/show_depth.vert", "../../shader_source/show_depth.frag");
    showDepthShader.Use();
    showDepthShader.setInt("showDepth", 0);
 
    CubeModel cubeModel("../../textures/wall.jpg", "../../textures/wall.jpg");
    QuadModel quad;

    //depth frame buffer

    unsigned int depthFramebuffer;
    glGenFramebuffers(1, &depthFramebuffer);
    
    unsigned int depthMap;
    glGenTextures(1, &depthMap);

    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
        depthWidth, depthHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depthFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------

        glBindFramebuffer(GL_FRAMEBUFFER, depthFramebuffer);
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT);
       
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(g_camera.GetZoom()), (float)800 / (float)600, 0.1f, 100.0f); 
        glm::mat4 view = g_camera.GetVieMatrix();
        glm::mat4 model = glm::mat4(1.0f);   

        depthShader.Use();
        depthShader.setMarix4f("model", model);
        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each
        glBindVertexArray(0);

        cubeModel.draw(depthShader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        showDepthShader.Use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        quad.draw(showDepthShader);



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------


    glfwTerminate();
    return 0;
}

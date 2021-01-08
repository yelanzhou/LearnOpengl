//#include <glad/glad.h>
//#include <GLFW/glfw3.h>


#include "initGL.h"
#include "Shader.h"
#include "Image2D.h"
#include "Texture2D.h"
#include "Light.h"
#include "Model.h"
#include "CubeModel.h"

#include <glm/gtc/matrix_transform.hpp>

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
// world space positions of our cubes

int main()
{
    GLFWwindow* window;
    if (!initGL(800, 600, window))
    {
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    Shader shader("..\\..\\shader_source\\model.vert", "..\\..\\shader_source\\model.frag");
    Shader colorShader("..\\..\\shader_source\\color.vert", "..\\..\\shader_source\\color.frag");
    


    shader.Use();
   // Model model("../../resources/backpack/backpack.obj");


    CubeModel  cube("../../textures/container2.png", "../../textures/container2_specular.png");

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        shader.Use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(g_camera.GetZoom()), (float)800 / (float)600, 0.1f, 100.0f);
        shader.setMarix4f("projection", projection);

        // camera/view transformation
        glm::mat4 view = g_camera.GetVieMatrix();
        shader.setMarix4f("view", view);

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
        //modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        //modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f, 0.3f, 0.3f));	// it's a bit too big for our scene, so scale it down
        shader.setMarix4f("model", modelMatrix);

        glStencilFunc(GL_ALWAYS, 1, 0Xff);
        glStencilMask(0xFF);

        cube.draw(shader);
       

        glStencilFunc(GL_NOTEQUAL, 1, 0xff);
        glStencilMask(0x00);
        //glDisable(GL_DEPTH_TEST);

        colorShader.Use();
        colorShader.setMarix4f("projection", projection);
        colorShader.setMarix4f("view", view);
        colorShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));

        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.05f, 1.05f, 1.05f));
       
        colorShader.setMarix4f("model", modelMatrix);
        cube.draw(colorShader);

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        //glEnable(GL_DEPTH_TEST);
        
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

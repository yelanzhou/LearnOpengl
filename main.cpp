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


    Shader shader("..\\..\\shader_source\\model.vert", "..\\..\\shader_source\\model.frag");
    Shader colorShader("..\\..\\shader_source\\color.vert", "..\\..\\shader_source\\color.frag");
    


    shader.Use();
   // Model model("../../resources/backpack/backpack.obj");


    CubeModel  cube("../../textures/container2.png", "../../textures/container2_specular.png");
    

    PlaneModel plane("../../textures/OIP.jpg", "../../textures/OIP.jpg");

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

        shader.Use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(g_camera.GetZoom()), (float)800 / (float)600, 0.1f, 100.0f);
        shader.setMarix4f("projection", projection);

        // camera/view transformation
        glm::mat4 view = g_camera.GetVieMatrix();
        shader.setMarix4f("view", view);

        glm::mat4 modelMatrix = glm::mat4(1.0f);
      
        shader.setMarix4f("model", modelMatrix);

        //cube.draw(shader);
        plane.draw(shader);

        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.0f, 0.0f, -1.0f));
        shader.setMarix4f("model", modelMatrix);
        
        cube.draw(shader);
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2.0f, 0.0f, 0.0f));
        shader.setMarix4f("model", modelMatrix);
        cube.draw(shader);

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

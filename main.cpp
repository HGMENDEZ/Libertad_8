#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"
//#include "camera.h"
#include "cameraSC.h"    
#include "window.h"
#include "teclado.h"
#include "main.h"
#include "model.h"


int main()
{
    Window();    
    {      /////////////////////////  MUESTRA LOS DATOS DE TARJETA Y VERSIONES DE OpenGL ////////////////////////////////////
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* version = glGetString(GL_VERSION);
        const GLubyte* glslVersion =
            glGetString(GL_SHADING_LANGUAGE_VERSION);

        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);

        printf("GL Vendor            : %s\n", vendor);
        printf("GL Renderer          : %s\n", renderer);
        printf("GL Version (string)  : %s\n", version);
        printf("GL Version (integer) : %d.%d\n", major, minor);
        printf("GLSL Version         : %s\n", glslVersion);


        ///////////// EXTENCIONES COMPATIBLES CON LA IMPLEMENTACION ACTUAL DE OpenGL ////////
        GLint nExtensions;
        glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);

        for (int i = 0; i < nExtensions; i++)
            printf("%s\n", glGetStringi(GL_EXTENSIONS, i));

    }


    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    // configure global opengl state
     glEnable(GL_DEPTH_TEST);


    // build and compile our shader zprogram
    Shader lightingShader("D:\\Dropbox\\0_Libertad\\Libertad_6\\Vertex\\m_l_V.vs", "D:\\Dropbox\\0_Libertad\\Libertad_6\\Fragment\\m_l_F.vs");
    Shader lightCubeShader("D:\\Dropbox\\0_Libertad\\Libertad_6\\Vertex\\l_c_V.vs", "D:\\Dropbox\\0_Libertad\\Libertad_6\\Fragment\\l_c_F.vs");

    Model ourModel("D:/Dropbox/0_Libertad/Hobots.obj"); // COLOCAR LAS TEXTURAS EN EL MISMO DIRECTORIO.
    Model ourModel1("D:/Dropbox/00PROYECTO/Importaciones/EsferaFBX.fbx");

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", cameraSC.Position);
        lightingShader.setFloat("material.shininess", 32.0f);

        // directional light
        lightingShader.setVec3("dirLight.direction", -0.5f, -0.5f, -0.5f);
        lightingShader.setVec3("dirLight.ambient", 0.25f, 0.25f, 0.25f);
        lightingShader.setVec3("dirLight.diffuse", 1.2f, 1.2f, 1.2f);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(cameraSC.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); // 
        glm::mat4 view = cameraSC.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);


        // render the loaded model
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));	// it's a bit too big for our scene, so scale it down
        lightingShader.setMat4("model", model);
        ourModel.Draw(lightingShader); //


//========================================================================
         //also draw the lamp object(s) -----NO BORRAR
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);


        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));	// it's a bit too big for our scene, so scale it down
        lightCubeShader.setMat4("model", model);
        ourModel1.Draw(lightCubeShader); //lightCubeShader
//========================================================================



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}




// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    cameraSC.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //    std::cout << "                          O  P  E  R  A  N  D  O  " << std::endl;
    cameraSC.ProcessMouseScroll(yoffset);
}
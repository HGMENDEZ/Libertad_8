

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

    //////////// set up vertex data (and buffer(s)) and configure vertex attributes
    //////////// ------------------------------------------------------------------
    //////////float vertices[] = {
    //////////    // positions          // normals           // texture coords
    //////////    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    //////////     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,


    //////////     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    //////////     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    //////////    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    //////////    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    //////////    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    //////////     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
    //////////     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    //////////     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    //////////    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    //////////    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    //////////    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    //////////    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    //////////    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    //////////    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    //////////    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    //////////    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    //////////     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    //////////     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    //////////     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    //////////     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    //////////     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    //////////     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    //////////    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    //////////     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
    //////////     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    //////////     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    //////////    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    //////////    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    //////////    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    //////////     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
    //////////     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    //////////     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    //////////    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    //////////    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    //////////};
    //////////// positions all containers
    //////////glm::vec3 cubePositions[] = {
    //////////    glm::vec3(0.0f,  0.0f,  0.0f),
    //////////    glm::vec3(2.0f,  5.0f, -15.0f),
    //////////    glm::vec3(-1.5f, -2.2f, -2.5f),
    //////////    glm::vec3(-3.8f, -2.0f, -12.3f),
    //////////    glm::vec3(2.4f, -0.4f, -3.5f),
    //////////    glm::vec3(-1.7f,  3.0f, -7.5f),
    //////////    glm::vec3(1.3f, -2.0f, -2.5f),
    //////////    glm::vec3(1.5f,  2.0f, -2.5f),
    //////////    glm::vec3(1.5f,  0.2f, -1.5f),
    //////////    glm::vec3(-1.3f,  1.0f, -1.5f)
    //////////};
    //////////// positions of the point lights
    //////////glm::vec3 pointLightPositions[] = {
    //////////    glm::vec3(0.7f,  0.2f,  2.0f),
    //////////    glm::vec3(2.3f, -3.3f, -4.0f),
    //////////    glm::vec3(-4.0f,  2.0f, -12.0f),
    //////////    glm::vec3(0.0f,  0.0f, -3.0f)
    //////////};
    //////////// first, configure the cube's VAO (and VBO)
    //////////unsigned int VBO, cubeVAO;
    //////////glGenVertexArrays(1, &cubeVAO);
    //////////glGenBuffers(1, &VBO);

    //////////glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //////////glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //////////glBindVertexArray(cubeVAO);
    //////////glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //////////glEnableVertexAttribArray(0);
    //////////glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //////////glEnableVertexAttribArray(1);
    //////////glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //////////glEnableVertexAttribArray(2);

    //////////// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    //////////unsigned int lightCubeVAO;
    //////////glGenVertexArrays(1, &lightCubeVAO);
    //////////glBindVertexArray(lightCubeVAO);

    //////////glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //////////// note that we update the lamp's position attribute's stride to reflect the updated buffer data
    //////////glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //////////glEnableVertexAttribArray(0);

    //////////// load textures (we now use a utility function to keep the code more organized)
    //////////// -----------------------------------------------------------------------------
    //////////unsigned int diffuseMap = loadTexture("D:\\Dropbox\\0_Libertad\\Imagenes\\Colores_Blanco.png");
    //////////unsigned int specularMap = loadTexture("D:\\Dropbox\\0_Libertad\\Imagenes\\Colores_Blanco.png");

    // shader configuration
    // --------------------
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
// -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", cameraSC.Position);
        lightingShader.setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
        lightingShader.setVec3("dirLight.direction", -0.5f, -0.5f, -0.5f);
        lightingShader.setVec3("dirLight.ambient", 0.4f, 0.4f, 0.4f);
        lightingShader.setVec3("dirLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("dirLight.specular", 2.0f, 2.0f, 2.0f);
        // point light 1
        //////////lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);     ///
        //////////lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        //////////lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        //////////lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        //////////lightingShader.setFloat("pointLights[0].constant", 1.0f);
        //////////lightingShader.setFloat("pointLights[0].linear", 0.09);
        //////////lightingShader.setFloat("pointLights[0].quadratic", 0.032);
        // point light 2
        //////////lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        //////////lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        //////////lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        //////////lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        //////////lightingShader.setFloat("pointLights[1].constant", 1.0f);
        //////////lightingShader.setFloat("pointLights[1].linear", 0.09);
        //////////lightingShader.setFloat("pointLights[1].quadratic", 0.032);
        //////////// point light 3
        //////////lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        //////////lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        //////////lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        //////////lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        //////////lightingShader.setFloat("pointLights[2].constant", 1.0f);
        //////////lightingShader.setFloat("pointLights[2].linear", 0.09);
        //////////lightingShader.setFloat("pointLights[2].quadratic", 0.032);
        //////////// point light 4
        //////////lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        //////////lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        //////////lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        //////////lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        //////////lightingShader.setFloat("pointLights[3].constant", 1.0f);
        //////////lightingShader.setFloat("pointLights[3].linear", 0.09);
        //////////lightingShader.setFloat("pointLights[3].quadratic", 0.032);
        
        // spotLight
        //////////lightingShader.setVec3("spotLight.position", cameraSC.Position);
        //////////lightingShader.setVec3("spotLight.direction", cameraSC.Front);
        //////////lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        //////////lightingShader.setVec3("spotLight.diffuse", 0.0f, 0.0f, 0.0f);
        //////////lightingShader.setVec3("spotLight.specular", 0.0f, 0.0f, 0.0f);
        lightingShader.setFloat("spotLight.constant", 1.0f);
        //////////lightingShader.setFloat("spotLight.linear", 0.09);
        //////////lightingShader.setFloat("spotLight.quadratic", 0.032);
        //////////lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        //////////lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(cameraSC.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); // 
        glm::mat4 view = cameraSC.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);



        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        //////////// bind diffuse map
        //////////glActiveTexture(GL_TEXTURE0);
        //////////glBindTexture(GL_TEXTURE_2D, diffuseMap);
        //////////// bind specular map
        //////////glActiveTexture(GL_TEXTURE1);
        //////////glBindTexture(GL_TEXTURE_2D, specularMap);

        //////////// render containers
        //////////glBindVertexArray(cubeVAO);
        //////////for (unsigned int i = 0; i < 10; i++)
        //////////{
        //////////    // calculate the model matrix for each object and pass it to shader before drawing
        //////////    glm::mat4 model = glm::mat4(1.0f);
        //////////    model = glm::translate(model, cubePositions[i]);
        //////////    float angle = 20.0f * i;
        //////////    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //////////    lightingShader.setMat4("model", model);

        //////////    glDrawArrays(GL_TRIANGLES, 0, 36);
        //////////}


// render the loaded model
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));	// it's a bit too big for our scene, so scale it down
        lightingShader.setMat4("model", model);
        ourModel.Draw(lightingShader); //
















        // also draw the lamp object(s)
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);


        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));	// it's a bit too big for our scene, so scale it down
        lightCubeShader.setMat4("model", model);
        ourModel1.Draw(lightCubeShader); //





        // we now draw as many light bulbs as we have point lights.
        //////////glBindVertexArray(lightCubeVAO);
        //////////for (unsigned int i = 0; i < 4; i++)
        //////////{
        //////////    model = glm::mat4(1.0f);
        //////////    model = glm::translate(model, pointLightPositions[i]);
        //////////    model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        //////////    lightCubeShader.setMat4("model", model);
        //////////    glDrawArrays(GL_TRIANGLES, 0, 36);
        //////////}

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //////////glDeleteVertexArrays(1, &cubeVAO);
    //////////glDeleteVertexArrays(1, &lightCubeVAO);
    //////////glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
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
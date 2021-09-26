#pragma once
#include <GLFW/glfw3.h>

#include "cameraSC.h"    //
#include "window.h"


#include "cameraControl.h"

GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(const char* path);

//void processInput(GLFWwindow* window);

// camera
//-----------------> 
//CameraSC cameraSC(glm::vec3(0.0f, 0.0f, 3.0f));
cameraControl cameraSC(glm::vec3(0.0f, 0.0f, 3.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);





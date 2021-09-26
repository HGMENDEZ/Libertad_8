#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>



extern GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);



const unsigned int SCR_WIDTH = 1800;
const unsigned int SCR_HEIGHT = 900;

int Window();

#endif


#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "derrro.h"
#include <vector>

const float YAW = -90.0f;
const float PITCH = 0.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class cameraSC
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    cameraSC(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    cameraSC(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    //////////////// returns the view matrix calculated using Euler Angles and the LookAt Matrix
    //////////////glm::mat4 GetViewMatrix()
    //////////////{
    //////////////    return glm::lookAt(Position, Position + Front, Up);
    //////////////}

    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors1();
};
#endif


#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "cameraSC.h"

#include <iostream>


cameraSC::cameraSC(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{

    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    // updateCameraVectors1();
}

cameraSC::cameraSC(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
    Position = glm::vec3(posX, posY, posZ);  //
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    // updateCameraVectors();
}

void cameraSC::updateCameraVectors1()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}
//#endif
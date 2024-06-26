#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum CameraMovement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    YAW,
    RYAW,
    PITCH,
    RPITCH
};

class Camera{
public:
    Camera();
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float fov;
    glm::mat4 getLookAt();
    void updateInput(CameraMovement movement, float delta_time);
    float Yaw;
    float Pitch;
    // float Roll;
private:
    void updateVector();
};
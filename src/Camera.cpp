#include "Camera.h"

Camera::Camera()
    : Position(glm::vec3(0.0f, 0.0f, 10.0f)), Front({0, 0, -1}), WorldUp({0, 1, 0}), Pitch(0), Yaw(-90.0f), fov(45.0f)
{
    updateVector();
}

void Camera::updateInput(CameraMovement movement, float delta_time) {
    float v = 50 * delta_time;
    float ang = 25.0f;
    if(movement == FORWARD)
        Position += Front * v;
    if(movement == BACKWARD)
        Position -= Front * v;
    if(movement == LEFT)
        Position -= Right * v;
    if(movement == RIGHT)
        Position += Right * v;
    if(movement == YAW)
        Yaw += ang * delta_time;
    if(movement == RYAW)
        Yaw -= ang * delta_time;
    if(movement == PITCH)
        Pitch += ang * delta_time;
    if(movement == RPITCH)
        Pitch -= ang * delta_time;
    
    if(Pitch > 89.0f)
        Pitch = 89.0f;
    if(Pitch < -89.0f)
        Pitch = -89.0f;
    
    updateVector();
}

void Camera::updateVector() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::getLookAt() {
    /*      view matrix
             Ex  Ey  Ez  0
    LookAt = Ux  Uy  Uz  0
             Target      0
             0   0   0   1
    */
    return glm::lookAt( Position,
                        Position + Front,
                        Up);
}
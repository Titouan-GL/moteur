
#include "camera.h"


Camera::Camera(float width, float height, glm::vec3 position){
    this->width = width;
    this->height = height;
    this->position = position;
}

Camera::Camera(float width, float height, float fov, float nearPlane, float farPlane, glm::vec3 position){
    this->width = width;
    this->height = height;
    this->position = position;
    this->fov = fov;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(position, position+forward(), up());
}

glm::mat4 Camera::getProjectionMatrix() const{
    return glm::perspective(glm::radians(fov), width/height, nearPlane, farPlane);
}


#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    // Startowa pozycja kamery (troche odsuniecie od srodka)
    position = glm::vec3(0.0f, 20.0f, 100.0f);
    target = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}

void Camera::moveForward(float speed) {
    position.z -= speed;
}

void Camera::moveBackward(float speed) {
    position.z += speed;
}

void Camera::moveLeft(float speed) {
    position.x -= speed;
    target.x -= speed; // Przesuwamy tez cel, zeby nie obracac kamery
}

void Camera::moveRight(float speed) {
    position.x += speed;
    target.x += speed;
}

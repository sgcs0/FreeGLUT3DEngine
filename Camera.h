#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    // Pozycje i wektory kamery
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    Camera();
    
    // Funkcja zwracajaca macierz widoku (do glLoadMatrixf)
    glm::mat4 getViewMatrix();

    // Proste metody poruszania
    void moveForward(float speed);
    void moveBackward(float speed);
    void moveLeft(float speed);
    void moveRight(float speed);
};

#endif

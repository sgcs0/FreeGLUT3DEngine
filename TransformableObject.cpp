#include "TransformableObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glut.h>

GameObject::GameObject() {
    modelMatrix = glm::mat4(1.0f); // Macierz jednostkowa na start
}

void GameObject::translate(float x, float y, float z) {
    modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
}

void GameObject::rotate(float angle, float x, float y, float z) {
    // Zamiana stopni na radiany, bo GLM uzywa radianow
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(x, y, z));
}

void GameObject::scale(float s) {
    modelMatrix = glm::scale(modelMatrix, glm::vec3(s, s, s));
}

void GameObject::reset() {
    modelMatrix = glm::mat4(1.0f);
}

void TransformableCube::draw() {
    glPushMatrix();
    // Zaladowanie aktualnej macierzy tego obiektu
    glMultMatrixf(glm::value_ptr(modelMatrix));
    
    // Rysowanie kostki
    glColor3f(1.0f, 0.5f, 0.0f); // Pomaranczowy
    glutWireCube(20.0f);
    
    glPopMatrix();
}

#ifndef TRANSFORMABLEOBJECT_H
#define TRANSFORMABLEOBJECT_H

#include <glm/glm.hpp>

// Klasa bazowa (Zadanie 2 - hierarchia)
class GameObject {
protected:
    glm::mat4 modelMatrix;

public:
    GameObject();
    virtual void draw() = 0; // Metoda czysto wirtualna

    // Metody do transformacji (Zadanie 3)
    void translate(float x, float y, float z);
    void rotate(float angle, float x, float y, float z);
    void scale(float s);
    void reset();
};

// Klasa szescianu (Zadanie 3 - rozszerzenie funkcjonalnosci)
class TransformableCube : public GameObject {
public:
    void draw(); // Nadpisanie metody draw
};

#endif

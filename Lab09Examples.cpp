#include "Lab09Examples.h"
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Lab09Examples::DrawExample1() {
    // Kod przepisany z Przykladu 1 (Rysunek 4 w PDF)
    glm::mat4 MatM = glm::mat4(1.0f);

    MatM = glm::translate(MatM, glm::vec3(10, 0, 10)); 
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(MatM));
    glColor3f(1, 0, 0);
    glutSolidCube(3);
    glPopMatrix();

    MatM = glm::translate(MatM, glm::vec3(20, 0, 0));
    MatM = glm::rotate(MatM, glm::radians(90.0f), glm::vec3(0, 1, 0));
    MatM = glm::translate(MatM, glm::vec3(-15, 0, 0));
    
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(MatM));
    glColor3f(0, 1, 0);
    glutSolidSphere(1, 12, 12);
    glPopMatrix();
}

void Lab09Examples::DrawExample2(float alpha, float beta) {
    // Kod przepisany z Przykladu 2 (Rysunek 5 w PDF - Uklad Sloneczny)
    glm::mat4 MatM = glm::mat4(1.0f);

    // Slonce
    glColor3f(1, 1, 0);
    glutSolidSphere(5, 12, 12);

    // Ziemia
    MatM = glm::rotate(MatM, alpha, glm::vec3(0, 1, 0));
    MatM = glm::translate(MatM, glm::vec3(40, 0, 0));

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(MatM));
    glColor3f(0, 0, 1);
    glutSolidSphere(3, 12, 12);
    glPopMatrix();

    // Ksiezyc
    MatM = glm::rotate(MatM, beta, glm::vec3(0, 1, 0));
    MatM = glm::translate(MatM, glm::vec3(10, 0, 0));

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(MatM));
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(1, 12, 12);
    glPopMatrix();
}

void Lab09Examples::DrawExample3(float angle) {
    // Kod przepisany z Przykladu 3 (Rysunek 6 w PDF)
    // Uwaga: Macierz widoku jest obslugiwana w Engine, tu tylko obiekty
    glm::mat4 MatM = glm::mat4(1.0f);
    
    // Animacja obrotu calosci
    MatM = glm::rotate(MatM, glm::radians(angle), glm::vec3(0, 1, 0));

    glm::mat4 MatRot120 = glm::rotate(glm::mat4(1.0f), glm::radians(120.0f), glm::vec3(0, 1, 0));
    glm::mat4 MatTra100 = glm::translate(glm::mat4(1.0f), glm::vec3(100, 0, 0));

    // 1. Zielony szescian
    glm::mat4 m1 = MatM * MatTra100;
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(m1));
    glColor3f(0, 1, 0); 
    glutSolidCube(50);
    glPopMatrix();

    // 2. Zolty czajnik
    glm::mat4 m2 = MatM * MatRot120 * MatTra100;
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(m2));
    glColor3f(1, 1, 0); 
    glutSolidTeapot(40);
    glPopMatrix();

    // 3. Niebieska sfera
    glm::mat4 m3 = MatM * MatRot120 * MatRot120 * MatTra100;
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(m3));
    glColor3f(0, 0, 1); 
    glutSolidSphere(50, 10, 10);
    glPopMatrix();
}

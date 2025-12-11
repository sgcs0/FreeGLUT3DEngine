#include "Engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Engine* Engine::instance = nullptr;

Engine::Engine() {
    width = 800;
    height = 600;
    rotX = 0.0f; rotY = 0.0f; rotZ = 0.0f;
    bgR = 0.2f; bgG = 0.2f; bgB = 0.2f;
    
    // Ustawiamy startowy tryb na przyklad 1 z lab 9
    currentMode = 11; 
    orthoMode = false; 
    
    // Inicjalizacja zmiennych animacji
    animAlpha = 0.0f;
    animBeta = 0.0f;
    animAngle = 0.0f;

    instance = this;
}

void Engine::init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Lab 09 - Transformacje");

    glutDisplayFunc(displayWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutMouseFunc(mouseWrapper);
    glutKeyboardFunc(keyboardWrapper);
    glutTimerFunc(16, timerWrapper, 0);

    glEnable(GL_DEPTH_TEST);

    printf("--- STEROWANIE LAB 09 ---\n");
    printf("[Z] Przyklad 1\n");
    printf("[X] Przyklad 2 (Uklad Sloneczny)\n");
    printf("[C] Przyklad 3 (Animacja)\n");
    printf("[V] Zadanie 3 (Transformowalny Szescian)\n");
    printf("--- STEROWANIE KAMERA ---\n");
    printf("[W/S] Przod / Tyl\n");
    printf("[A/D] Lewo / Prawo\n");
    printf("--- TRANSFORMACJE SZESCIANU (Tryb V) ---\n");
    printf("[T] Przesun, [R] Obroc, [G] Skaluj\n");
    printf("[1-0] Stare tryby\n");
}

void Engine::run() {
    glutMainLoop();
}

void Engine::render() {
    glClearColor(bgR, bgG, bgB, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // --- ZADANIE 1: OBSLUGA KAMERY ---
    // Pobieramy macierz widoku z naszej klasy Camera
    glm::mat4 viewMatrix = camera.getViewMatrix();
    // Ladujemy ja do OpenGL
    glLoadMatrixf(glm::value_ptr(viewMatrix));
    
    // Ewentualne dodatkowe rotacje calej sceny (ze starych labow)
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

    switch (currentMode) {
        // --- NOWE TRYBY LAB 09 ---
        case 11: // Przyklad 1
            labExamples.DrawExample1(); 
            break;
        case 12: // Przyklad 2
            labExamples.DrawExample2(animAlpha, animBeta);
            break;
        case 13: // Przyklad 3
            labExamples.DrawExample3(animAngle);
            break;
        case 14: // Zadanie 3 (Szescian)
            myCube.draw();
            break;

        // --- STARE TRYBY ---
        case 1: glColor3f(1,1,0); manualShapes.DrawPrimitive(2); break;
        case 2: manualShapes.DrawIndexedCube(); break;
        case 3: glColor3f(0,1,1); manualShapes.DrawPrimitive(8); break;
        case 4: glColor3f(1,0,1); proceduralShapes.DrawCylinder(); break;
        case 5: glColor3f(0,0.5,1); proceduralShapes.DrawCone(); break;
        case 6: glColor3f(1,0.5,0); proceduralShapes.DrawPyramid(); break;
        case 7: glColor3f(1,1,1); manualShapes.DrawPrimitive(1); break;
        case 8: glColor3f(0,1,0); manualShapes.DrawPrimitive(5); break;
        case 9: glColor3f(1,0,0); manualShapes.DrawPrimitive(3); break;
        case 0: glColor3f(0.5,0,0.5); manualShapes.DrawPrimitive(7); break;
    }

    glutSwapBuffers();
}

void Engine::update() {
    // Aktualizacja animacji
    animAlpha += 0.02f;
    animBeta += 0.05f;
    animAngle += 1.0f;
    
    glutPostRedisplay();
    glutTimerFunc(16, timerWrapper, 0);
}

void Engine::reshape(int w, int h) {
    if (h == 0) h = 1;
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspect = (float)w / h;
    
    // Uzywamy GLM do macierzy projekcji (zgodnie z instrukcja)
    glm::mat4 projection;
    
    if (orthoMode) {
        if (w >= h)
            projection = glm::ortho(-50.0f * aspect, 50.0f * aspect, -50.0f, 50.0f, -500.0f, 500.0f);
        else
            projection = glm::ortho(-50.0f, 50.0f, -50.0f / aspect, 50.0f / aspect, -500.0f, 500.0f);
    } else {
        // Zwiekszylem zasieg widzenia (Far plane) do 500, zeby widziec przyklady
        projection = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 500.0f);
    }
    
    glLoadMatrixf(glm::value_ptr(projection));
    glMatrixMode(GL_MODELVIEW);
}

void Engine::handleMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) { bgR=0.8f; bgG=0.1f; bgB=0.1f; }
        else if (button == GLUT_MIDDLE_BUTTON) { bgR=0.1f; bgG=0.8f; bgB=0.1f; }
        else if (button == GLUT_RIGHT_BUTTON) { bgR=0.1f; bgG=0.1f; bgB=0.8f; }
    }
}

void Engine::handleKeyboard(unsigned char key, int x, int y) {
    float camSpeed = 2.0f;

    switch (key) {
        // Sterowanie kamera (WASD - bo wygodniej)
        case 'w': camera.moveForward(camSpeed); break;
        case 's': camera.moveBackward(camSpeed); break;
        case 'a': camera.moveLeft(camSpeed); break;
        case 'd': camera.moveRight(camSpeed); break;
        
        // Wybor trybow Lab 09
        case 'z': currentMode = 11; break;
        case 'x': currentMode = 12; break;
        case 'c': currentMode = 13; break;
        case 'v': currentMode = 14; myCube.reset(); break; // Reset kostki przy wejsciu
        
        // Transformacje kostki (Zadanie 3)
        case 't': myCube.translate(5.0f, 0.0f, 0.0f); break; // Przesun w prawo
        case 'r': myCube.rotate(15.0f, 0.0f, 1.0f, 0.0f); break; // Obroc wokol Y
        case 'g': myCube.scale(1.1f); break; // Powieksz

        // Stare skroty
        case 'q': rotZ -= 5.0f; break; 
        case 'e': rotZ += 5.0f; break; 
        case 'p': orthoMode = !orthoMode; reshape(width, height); break;
            
        case '1': currentMode = 1; break; 
        case '2': currentMode = 2; break; 
        case '3': currentMode = 3; break; 
        case '4': currentMode = 4; break; 
        case '5': currentMode = 5; break; 
        case '6': currentMode = 6; break;
        case '7': currentMode = 7; break;
        case '8': currentMode = 8; break;
        case '9': currentMode = 9; break;
        case '0': currentMode = 0; break;
    }
}

void Engine::displayWrapper() { instance->render(); }
void Engine::reshapeWrapper(int w, int h) { instance->reshape(w, h); }
void Engine::mouseWrapper(int b, int s, int x, int y) { instance->handleMouse(b, s, x, y); }
void Engine::keyboardWrapper(unsigned char k, int x, int y) { instance->handleKeyboard(k, x, y); }
void Engine::timerWrapper(int v) { instance->update(); }

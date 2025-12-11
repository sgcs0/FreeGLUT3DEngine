#ifndef ENGINE_H
#define ENGINE_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include "SimpleShapes.h"
#include "ManualShapes.h"
#include "ProceduralShapes.h"

// --- NOWE PLIKI LAB 09 ---
#include "Camera.h"
#include "TransformableObject.h"
#include "Lab09Examples.h"

class Engine {
private:
    int width, height;
    float rotX, rotY, rotZ;
    float bgR, bgG, bgB;
    int currentMode; 
    bool orthoMode; 

    SimpleShapes simpleShapes; 
    ManualShapes manualShapes;
    ProceduralShapes proceduralShapes;
    
    // --- NOWE ZMIENNE LAB 09 ---
    Camera camera;                  // Zadanie 1
    TransformableCube myCube;       // Zadanie 3
    Lab09Examples labExamples;      // Przyklady z PDF
    
    float animAlpha; // Do przykladu 2
    float animBeta;  // Do przykladu 2
    float animAngle; // Do przykladu 3

    static Engine* instance;

public:
    Engine();
    void init(int argc, char** argv);
    void run();

private:
    void render();
    void update();
    void reshape(int w, int h);
    void handleMouse(int button, int state, int x, int y);
    void handleKeyboard(unsigned char key, int x, int y);
    
    static void displayWrapper();
    static void reshapeWrapper(int w, int h);
    static void mouseWrapper(int button, int state, int x, int y);
    static void keyboardWrapper(unsigned char key, int x, int y);
    static void timerWrapper(int value);
};

#endif

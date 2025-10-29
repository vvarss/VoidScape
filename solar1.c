#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

float angleSun = 0.0f;
float glow = 0.0f;
float camAngle = 0.0f;
float camRadius = 12.0f;
float camHeight = 15.0f;  // higher for top-down view
float anglePlanet[8] = {0.0f};
float selfRotate[8] = {0.0f};
float orbitSpeed[] = {2.35, 1.75, 1.45, 1.2, 0.65, 0.5, 0.35, 0.25};
float spinSpeed[]  = {3.5, 3, 2.5, 2, 1.5, 1, 1, 0.5};
float distanceP[] = {1.2, 1.8, 2.5, 3.2, 4.2, 5.2, 6.0, 6.8};
float sizeP[] = {0.1, 0.15, 0.17, 0.2, 0.35, 0.32, 0.27, 0.25};

float stars[200][3];

void generateStars() {
    srand(time(NULL));
    for (int i = 0; i < 200; i++) {
        stars[i][0] = (rand() % 200 - 100) / 10.0;
        stars[i][1] = (rand() % 200 - 100) / 10.0;
        stars[i][2] = -(rand() % 100);
    }
}

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat lightPos[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat amb[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diff[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat spec[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
}

void drawNebula() {
    glDisable(GL_LIGHTING);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for (int i = 0; i < 300; i++) {
        float x = (rand()%400 - 200)/10.0f;
        float y = (rand()%400 - 200)/10.0f;
        float z = -(rand()%100);
        float glowEffect = 0.2 + 0.2 * fabs(sin(glow + i));
        glColor4f(0.2*glowEffect, 0.05*glowEffect, 0.3*glowEffect, 0.3);
        glVertex3f(x, y, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawStars() {
    glDisable(GL_LIGHTING);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 200; i++) {
        float twinkle = (sin(glow + i * 0.1) + 1.0) / 2.0;
        if (i % 2 == 0) twinkle = 1 - twinkle;
        glColor3f(twinkle, twinkle, twinkle);
        glVertex3f(stars[i][0], stars[i][1], stars[i][2]);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawOrbit(float dist, float phase) {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float rad = i * M_PI / 180.0;
        float glowEffect = 0.5 + 0.5 * sin(glow + phase + i * 0.05);
        glColor3f(0.3 * glowEffect, 0.7 * glowEffect, 1.0);
        glVertex3f(cos(rad) * dist, 0, sin(rad) * dist);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawPlanet(float dist, float size, float orbitAngle, float selfRot, float r, float g, float b) {
    glPushMatrix();
    glRotatef(orbitAngle, 0, 1, 0);
    glTranslatef(dist, 0, 0);
    glRotatef(selfRot, 0, 1, 0);
    glColor3f(r, g, b);
    glutSolidSphere(size, 25, 25);
    glPopMatrix();
}

void drawSaturnRing(float dist) {
    glPushMatrix();
    glRotatef(anglePlanet[5], 0, 1, 0);
    glTranslatef(dist, 0, 0);
    glRotatef(25, 1, 0, 0);
    glDisable(GL_LIGHTING);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i++) {
        float rad = i * M_PI / 180.0;
        float glowEffect = 0.5 + 0.5 * sin(glow);
        glColor3f(0.8, 0.7 * glowEffect, 0.9);
        glVertex3f(cos(rad) * 0.5, 0, sin(rad) * 0.5);
        glVertex3f(cos(rad) * 0.8, 0, sin(rad) * 0.8);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void drawSun() {
    GLfloat sunEmission[] = {1.0, 0.8 + 0.2 * fabs(sin(glow)), 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, sunEmission);
    glColor3f(1.0, 0.9, 0.0);
    glutSolidSphere(0.7 + 0.05 * sin(glow * 2), 50, 50);
    GLfloat noEmission[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Rotating top-down camera
    float camX = camRadius * sin(camAngle);
    float camZ = camRadius * cos(camAngle);
    gluLookAt(camX, camHeight, camZ,  // Camera position
              0.0, 0.0, 0.0,         // Look at center
              0.0, 0.0, -1.0);       // Up vector for top-down view

    drawNebula();
    drawStars();
    drawSun();

    for (int i = 0; i < 8; i++) {
        drawOrbit(distanceP[i], i * 0.5);
    }

    drawPlanet(distanceP[0], sizeP[0], anglePlanet[0], selfRotate[0], 0.6, 0.6, 0.6);
    drawPlanet(distanceP[1], sizeP[1], anglePlanet[1], selfRotate[1], 0.8, 0.5, 0.2);
    drawPlanet(distanceP[2], sizeP[2], anglePlanet[2], selfRotate[2], 0.2, 0.3, 1.0);
    drawPlanet(distanceP[3], sizeP[3], anglePlanet[3], selfRotate[3], 1.0, 0.2, 0.2);
    drawPlanet(distanceP[4], sizeP[4], anglePlanet[4], selfRotate[4], 1.0, 0.8, 0.4);
    drawPlanet(distanceP[5], sizeP[5], anglePlanet[5], selfRotate[5], 1.0, 0.6, 0.2);
    drawSaturnRing(distanceP[5]);
    drawPlanet(distanceP[6], sizeP[6], anglePlanet[6], selfRotate[6], 0.4, 0.7, 1.0);
    drawPlanet(distanceP[7], sizeP[7], anglePlanet[7], selfRotate[7], 0.3, 0.4, 1.0);

    glutSwapBuffers();
}

void update(int value) {
    angleSun += 0.5;
    for (int i = 0; i < 8; i++) {
        anglePlanet[i] += orbitSpeed[i];
        selfRotate[i] += spinSpeed[i];
        if (anglePlanet[i] > 360) anglePlanet[i] -= 360;
        if (selfRotate[i] > 360) selfRotate[i] -= 360;
    }
    glow += 0.05;
    camAngle += 0.002f;  // slow camera rotation
    if(camAngle > 2*M_PI) camAngle -= 2*M_PI;

    glutPostRedisplay();
    glutTimerFunc(33, update, 0);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.05, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.3, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);

    generateStars();
    initLighting();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 700);
    glutCreateWindow("3D Solar System - Top-Down Rotating Camera");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(33, update, 0);
    glutMainLoop();
    return 0;
}

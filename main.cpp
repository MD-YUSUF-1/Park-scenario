#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

// Airplane animation
GLfloat planeX = 1.2f;
GLfloat planeSpeed = 0.004f;


void drawEllipse(GLfloat x, GLfloat y, GLfloat radiusX, GLfloat radiusY, int triangleAmount) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    GLfloat twicePi = 2.0f * PI;

    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radiusX * cos(i * twicePi / triangleAmount)),
            y + (radiusY * sin(i * twicePi / triangleAmount))
        );
    }

    glEnd();
}


void init() {
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, int triangleAmount) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    GLfloat twicePi = 2.0f * PI;
    for(int i = 0; i <= triangleAmount; i++)
        {
            glVertex2f( x + (radius * cos(i *  twicePi / triangleAmount)),
                        y + (radius * sin(i * twicePi / triangleAmount)) );
        }
    glEnd();
}

void drawQuad(GLfloat x, GLfloat y, GLfloat w, GLfloat h) {

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawTriangle(GLfloat x, GLfloat y, GLfloat w, GLfloat h) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + h);
    glVertex2f(x - w, y);
    glVertex2f(x + w, y);
    glEnd();
}


void drawSun() {
    glColor3f(1.0f, 1.0f, 0.0f);
    drawFilledCircle(0.45f, 0.75f, 0.15f, 100);
}


void drawCloud(GLfloat cx, GLfloat cy, GLfloat size) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(cx, cy, size, 30);

    glTranslatef(+0.05f, 0.05f, 0.0f);
    drawFilledCircle(cx, cy, size, 30);

   glTranslatef(+0.07f, 0.01f, 0.0f);
    drawFilledCircle(cx, cy, size, 30);

    glTranslatef(+0.07f, -0.01f, 0.0f);
   drawFilledCircle(cx, cy, size, 30);

    glTranslatef(+0.03f, -0.05f, 0.0f);
    drawFilledCircle(cx, cy, size, 30);

    glTranslatef(-0.03f, -0.05f, 0.0f);
    drawFilledCircle(cx, cy, size, 30);

    glTranslatef(-0.06f, -0.02f, 0.0f);
    drawFilledCircle(cx, cy, size, 30);

    glTranslatef(-0.06f, -0.0f, 0.0f);
    drawFilledCircle(cx, cy, size, 30);

    glTranslatef(-0.06f, 0.02f, 0.0f);
    drawFilledCircle(cx, cy, size, 30);

    glTranslatef(0.09f, 0.05f, 0.0f);
    drawFilledCircle(cx, cy, size*1.15, 30);

    glLoadIdentity();
}


void drawCityBuildings() {
    glColor3f(0.55f, 0.60f, 0.68f);
    drawQuad(-0.5f, 0.0f, 0.1f, 0.20f);

    glTranslatef(+0.1f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0,1.5,0);
    drawQuad(-0.5f, 0.0f, 0.1f, 0.20f);
    glPopMatrix();

    glTranslatef(+0.1f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0,0.7,0);
    drawQuad(-0.5f, 0.0f, 0.08f, 0.20f);
    glPopMatrix();

    glTranslatef(+0.08f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0,1.2,0);
    drawQuad(-0.5f, 0.0f, 0.09f, 0.20f);
    glPopMatrix();

    glTranslatef(+0.09f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0,2.0,0);
    drawQuad(-0.5f, 0.0f, 0.1f, 0.20f);
    glPopMatrix();

    glTranslatef(+0.1f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0,1.0,0);
    drawQuad(-0.5f, 0.0f, 0.12f, 0.20f);
    glPopMatrix();

    glTranslatef(+0.12f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0,1.3,0);
    drawQuad(-0.5f, 0.0f, 0.1f, 0.20f);
    glPopMatrix();

    glTranslatef(+0.1f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0,0.9,0);
    drawQuad(-0.5f, 0.0f, 0.09f, 0.20f);
    glPopMatrix();

    glTranslatef(+0.09f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0,0.7,0);
    drawQuad(-0.5f, 0.0f, 0.08f, 0.20f);
    glPopMatrix();

    glTranslatef(+0.08f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0,0.3,0);
    drawQuad(-0.5f, 0.0f, 0.08f, 0.20f);
    glLoadIdentity();


}


// Draw grass
void drawGrass() {
    // Main grass area
    glColor3f(0.30f, 0.70f, 0.20f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 0.04f);
    glVertex2f(-1.0f, 0.04f);
    glEnd();


    glColor3f(0.4f, 0.8f, 0.22f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.4f, 0.01f);
    glVertex2f(-1.0f, -0.1f);
    glVertex2f(-1.0f, 0.1f);
    glVertex2f(-0.5f, 0.08f);
    glVertex2f(0.0f, 0.04f);
    glEnd();


    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.6f, 0.04f);
    glVertex2f(1.0f, 0.04f);
    glVertex2f(1.0f, 0.15f);
    glVertex2f(0.7f, 0.12f);
    glVertex2f(0.2f, 0.04f);
    glEnd();
}



void drawPineTree(GLfloat x, GLfloat y) {

    glTranslatef(x, y, 0.0f);
    glColor3f(0.45f, 0.28f, 0.10f);
    glPushMatrix();
    drawQuad(0.0f, 0.0f, 0.03f, 0.08f);
    glPopMatrix();

    glTranslatef(0.015f, 0.08f, 0.0f);
    glColor3f(0.10f, 0.55f, 0.15f);
    glPushMatrix();
    drawTriangle(0.0f, 0.0f, 0.12f, 0.14f);
    glPopMatrix();

    glTranslatef(0.0f, 0.09f, 0.0f);
    glPushMatrix();
        glScalef(0.8f, 1.0f, 0.0f);
        drawTriangle(0.0f, 0.0f, 0.12f, 0.13f);
    glPopMatrix();

    glTranslatef(0.0f, 0.09f, 0.0f);
    glPushMatrix();
        glScalef(0.6f, 1.0f, 0.0f);
        drawTriangle(0.0f, 0.0f, 0.12f, 0.12f);
    glPopMatrix();

    glLoadIdentity();
}


void drawPath() {
    glColor3f(0.76f, 0.64f, 0.48f);


    glBegin(GL_QUADS);
    glVertex2f(-0.64f, -0.03f);
    glVertex2f(-0.55f, -0.04f);
    glVertex2f(-0.57f, -0.089f);
    glVertex2f(-0.72f, -0.055f);
    glEnd();

    glBegin(GL_QUADS);
     glVertex2f(-0.55f, -0.04f);
    glVertex2f(-0.57f, -0.089f);
    glVertex2f( 1.0f, -0.1f);
    glVertex2f(1.0f, -0.052f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f( 0.1f, -0.05f);
    glVertex2f( 0.1f, -0.2f);
    glVertex2f( -0.1f, -0.20f);
    glVertex2f( -0.1f, -0.05f);
    glEnd();

    drawFilledCircle(-0.014,-0.38,0.24,30);

    glBegin(GL_QUADS);
    glVertex2f( -0.22f, -0.48f);
    glVertex2f( -0.42f, -0.60f);
    glVertex2f( -0.28f, -0.76f);
    glVertex2f( -0.008f, -0.61f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f( -0.42f, -0.60f);
    glVertex2f( -0.28f, -0.76f);
    glVertex2f(-0.5f, -0.74f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f( -0.28f, -0.76f);
    glVertex2f(-0.5f, -0.74f);
    glVertex2f( -0.65f, -1.0f);
    glVertex2f( -0.4f, -1.0f);
    glEnd();
}


void drawPond() {
    glColor3f(0.25f, 0.55f, 0.80f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.73f, -0.40f);
    glVertex2f(-0.67f, -0.54f);
    glVertex2f(-0.5f, -0.54f);
    glVertex2f(-0.33f, -0.36f);
    glVertex2f(-0.38f, -0.27f);
    glVertex2f(-0.28f, -0.11f);
    glVertex2f(-0.54f, -0.11f);
    glVertex2f(-0.62f, -0.21f);
    glVertex2f(-0.67f, -0.24f);
    glEnd();

    glColor3f(0.50f, 0.40f, 0.20f);
    glBegin(GL_QUADS);
    glVertex2f(-0.73f, -0.40f);
    glVertex2f(-0.67f, -0.24f);
    glVertex2f(-0.66f, -0.25f);
    glVertex2f(-0.71f, -0.40f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.67f, -0.24f);
    glVertex2f(-0.66f, -0.25f);
    glVertex2f(-0.61f, -0.22f);
    glVertex2f(-0.62f, -0.21f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.61f, -0.22f);
    glVertex2f(-0.62f, -0.21f);
    glVertex2f(-0.54f, -0.11f);
    glVertex2f(-0.52f, -0.11f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.73f, -0.40f);
    glVertex2f(-0.71f, -0.40f);
    glVertex2f(-0.665f, -0.535f);
    glVertex2f(-0.67f, -0.54f);
    glEnd();

}


void drawRoundTree(GLfloat x, GLfloat y ) {

    glColor3f(0.45f, 0.28f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-0.85f, 0.027f);
    glVertex2f(-0.81f, 0.027f);
    glVertex2f(-0.79f, -0.32f);
    glVertex2f(-0.87f, -0.32f);
    glEnd();

     glBegin(GL_QUADS);
    glVertex2f(-0.83f, -0.09f);
    glVertex2f(-0.93f, -0.023f);
    glVertex2f(-0.91f, -0.0f);
    glVertex2f(-0.83f, -0.047f);
    glEnd();

     glBegin(GL_QUADS);
    glVertex2f(-0.82f, -0.06f);
    glVertex2f(-0.73f, 0.0f);
    glVertex2f(-0.72f, -0.02f);
    glVertex2f(-0.82f, -0.09f);
    glEnd();

    glColor3f(0.20f, 0.62f, 0.14f);
    drawFilledCircle(-0.83,0.18, 0.16, 30);
    drawFilledCircle(-0.66,0.072, 0.13, 30);
    drawFilledCircle(-1.0,0.062, 0.13, 30);

}


void drawBridge(){

    glColor3f(0.60f, 0.38f, 0.18f);

    glBegin(GL_QUADS);
    glVertex2f(-0.56, -0.14);
    glVertex2f(-0.30, -0.14);
    glVertex2f(-0.27, -0.093);
    glVertex2f(-0.525, -0.090);
    glEnd();

glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(5.0);
    glBegin(GL_LINES);
        glVertex2f(-0.56, -0.14);
        glVertex2f(-0.417, -0.0055);
    glEnd();

    glLineWidth(5.0);
    glBegin(GL_LINES);
        glVertex2f(-0.417, -0.0055);
        glVertex2f(-0.30, -0.14);
    glEnd();

    glLineWidth(5.0);
    glBegin(GL_LINES);
        glVertex2f(-0.525, -0.090);
        glVertex2f(-0.38, 0.055);
    glEnd();

    glLineWidth(5.0);
    glBegin(GL_LINES);
        glVertex2f(-0.38, 0.055);
        glVertex2f(-0.27, -0.093);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.34, -0.14);
        glVertex2f(-0.34, -0.095);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.38, -0.046);
        glVertex2f(-0.38, -0.14);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.425, -0.14);
        glVertex2f(-0.425, -0.0143);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.51, -0.095);
        glVertex2f(-0.46, -0.05);
    glEnd();

        glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.46, -0.053);
        glVertex2f(-0.46, -0.14);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.51, -0.14);
        glVertex2f(-0.51, -0.095);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.48, -0.09);
        glVertex2f(-0.48, -0.045);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.44, -0.0044);
        glVertex2f(-0.44, -0.09);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.41, 0.027);
        glVertex2f(-0.41, -0.090);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.37, 0.039);
        glVertex2f(-0.37, -0.091);
    glEnd();

        glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.33, -0.015);
        glVertex2f(-0.33, -0.091);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.29, -0.063);
        glVertex2f(-0.29, -0.091);
    glEnd();

}



void drawSwingSet() {

    glColor3f(0.44f, 0.27f, 0.10f);
    glLineWidth(3.5f);
    glBegin(GL_LINES);
    glVertex2f(0.44f,-0.008f);
    glVertex2f(0.38f,-0.25f);
    glVertex2f(0.44f,-0.008f);
    glVertex2f(0.48f,-0.25f);
    glEnd();


    glTranslatef(+0.35f, 0.0f, 0.0f);
    glLineWidth(3.5f);
    glBegin(GL_LINES);
    glVertex2f(0.44f,-0.008f);
    glVertex2f(0.38f,-0.25f);
    glVertex2f(0.44f,-0.008f);
    glVertex2f(0.48f,-0.25f);
    glEnd();

    glTranslatef(-0.35f, 0.0f, 0.0f);
    glLineWidth(3.5f);
    glBegin(GL_LINES);
    glVertex2f(0.44f,-0.008f);
    glVertex2f(0.79f,-0.008f);
    glEnd();

    glColor3f(0.86f, 0.79f, 0.56f);
    glBegin(GL_QUADS);
    glVertex2f(0.55f,-0.15f);
    glVertex2f(0.53f,-0.20f);
    glVertex2f(0.585f,-0.20f);
    glVertex2f(0.605f,-0.15f);
    glEnd();

    glColor3f(0.44f, 0.27f, 0.10f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(0.54f,-0.008f);
    glVertex2f(0.54f,-0.18f);
    glVertex2f(0.59f,-0.008f);
    glVertex2f(0.59f,-0.18f);
    glEnd();

    glColor3f(0.86f, 0.79f, 0.56f);
    glBegin(GL_QUADS);
    glVertex2f(0.66f,-0.15f);
    glVertex2f(0.64f,-0.20f);
    glVertex2f(0.695f,-0.20f);
    glVertex2f(0.715f,-0.15f);
    glEnd();

    glColor3f(0.44f, 0.27f, 0.10f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(0.65f,-0.008f);
    glVertex2f(0.65f,-0.18f);
    glVertex2f(0.70f,-0.008f);
    glVertex2f(0.70f,-0.18f);
    glEnd();

}


void drawAirplane(float x, float y) {

    glColor3f(0.92f, 0.92f, 0.92f);
    drawEllipse(x, y, 0.1f, 0.04f, 50);


    glBegin(GL_TRIANGLES);
    glVertex2f(x + 0.098f, y-0.015);
    glVertex2f(x + 0.135f, y-0.005);
    glVertex2f(x + 0.095f, y + 0.015f);
    glEnd();

    glColor3f(0.85f, 0.85f, 0.88f);
    glBegin(GL_POLYGON);
    glVertex2f(x-0.03,        y-0.01);
    glVertex2f(x + 0.011f, y-0.01);
    glVertex2f(x + 0.001f, y - 0.074f);
    glVertex2f(x - 0.04f, y - 0.074f);
    glEnd();

    // Tail wing
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.095f, y + 0.027f);
    glVertex2f(x - 0.065f, y + 0.027f);
    glVertex2f(x - 0.065f, y + 0.060f);
    glVertex2f(x - 0.095f, y + 0.060f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x - 0.084f, y);
    glVertex2f(x - 0.053f, y);
    glVertex2f(x - 0.062f, y + 0.067f);
    glVertex2f(x - 0.084f, y + 0.060f);
    glEnd();

//    // Engine
//    glColor3f(0.50f, 0.50f, 0.55f);
//    drawFilledCircle(x + 0.011f, y - 0.050f, 0.013f, 40);
//
    // Window strip
    glColor3f(0.55f, 0.82f, 0.97f);
    for (int i = 0; i < 5; i++)
        drawFilledCircle(x - 0.011f + i * 0.022f, y + 0.007f, 0.010f, 30);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();



    drawSun();


    drawCloud(-0.75f, 0.82f, 0.055f);
    drawCloud(-0.35f, 0.65f, 0.055f);
    drawCloud(0.70f,0.85f, 0.055f);


    drawCityBuildings();


    drawGrass();


    drawPath();

    drawPond();

    drawBridge();


    drawPineTree(-0.55f, 0.03f);
    drawPineTree( -0.10f, -0.02f);
    drawPineTree( 0.02f, 0.02f);
    drawPineTree( 0.70f,0.0f);
    glPushMatrix();
    glScalef(1.20f, 1.40f, 0.0f);
    drawPineTree( 0.70f,0.0f);
    glPopMatrix();


    drawRoundTree(-0.85f, -0.35f);


//    drawFountain();
//
//    // 11. Benches
//    drawBench(-0.15f, -0.42f, 0.10f); // left of fountain
//    drawBench( 0.35f, -0.42f, 0.10f); // right of fountain
//    drawBench(-0.52f, -0.72f, 0.09f); // near pond
//

    glTranslatef(0,-0.2f,0);
    drawSwingSet();
    glLoadIdentity();


    drawAirplane(0.05f, 0.633f);

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(80, 50);
    glutCreateWindow("Park Scenario");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

}









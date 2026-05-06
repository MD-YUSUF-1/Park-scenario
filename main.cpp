#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

// Airplane animation
GLfloat planeY = 0.7f;
GLfloat planeUpperLimit = 0.85f;
GLfloat planeLowerLimit = 0.62f;


GLfloat planePosition = 0.05f;
GLfloat planeSpeed = 0.005f;

GLfloat cloudPosition1 = -0.75f;
GLfloat cloudPosition2 = -0.35f;
GLfloat cloudPosition3 = 0.70f;
GLfloat cloudSpeed = 0.002f;

int rainMode = 0;
float rainDropY[600];
float rainDropX[600];
int nightMode = 0;

void drawStars()
{
    glPointSize(2.0f);

    glBegin(GL_POINTS);

    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.9f, 0.9f);
    glVertex2f(-0.7f, 0.8f);
    glVertex2f(-0.5f, 0.95f);
    glVertex2f(-0.2f, 0.75f);
    glVertex2f(0.0f, 0.92f);
    glVertex2f(0.2f, 0.82f);
    glVertex2f(0.5f, 0.90f);
    glVertex2f(0.8f, 0.78f);
    glVertex2f(0.65f, 0.96f);

    glEnd();
}

void initRain() {
    for (int i = 0; i < 600; i++) {

        // X between -1 and 1
        rainDropX[i] = ((rand() % 2000) / 1000.0f) - 1.0f;

        // Y between -1 and 1
        rainDropY[i] = ((rand() % 2000) / 1000.0f) - 1.0f;
    }
}



void keyboard(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        rainMode = !rainMode;
    }
    if (key == 'n' || key == 'N')
    {
        nightMode = !nightMode;
    }
}

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:

            planeY += 0.05f;

            // Upper limit
            if(planeY > planeUpperLimit)
                planeY = planeUpperLimit;

            break;

        case GLUT_KEY_DOWN:

            planeY -= 0.05f;

            // Lower limit
            if(planeY < planeLowerLimit)
                planeY = planeLowerLimit;

            break;

        case GLUT_KEY_LEFT:
            break;

        case GLUT_KEY_RIGHT:
            break;
    }

    glutPostRedisplay();
}

void init() {

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
}



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


void drawSun()
{
    // NIGHT MODE
    if(nightMode)
    {
        // Moon
        glColor3f(0.9f, 0.9f, 0.95f);
        drawFilledCircle(0.45f, 0.75f, 0.12f, 100);

        // Moon shadow
        glColor3f(0.05f, 0.05f, 0.12f);
        drawFilledCircle(0.49f, 0.78f, 0.10f, 100);
    }

    // RAIN MODE
    else if(rainMode)
    {
        glColor3f(0.25f, 0.25f, 0.32f);
        drawFilledCircle(0.45f, 0.75f, 0.15f, 100);
    }

    // DAY MODE
    else
    {
        glColor3f(1.0f, 1.0f, 0.0f);
        drawFilledCircle(0.45f, 0.75f, 0.15f, 100);
    }
}

void updateCloud(int v)
{
    if(cloudPosition1 > 1.9 && !rainMode)
        cloudPosition1 = -1.9f;
    if (cloudPosition2 >1.4 && !rainMode)
            cloudPosition2 = -1.4;
    if (cloudPosition3 >1.0 && !rainMode)
            cloudPosition3 = -1.0;

    cloudPosition1 = cloudPosition1 + cloudSpeed;
    cloudPosition2 = cloudPosition2 + cloudSpeed;
    cloudPosition3 = cloudPosition3 + cloudSpeed;

	glutPostRedisplay();
	glutTimerFunc(10, updateCloud, 0);
}
void drawCloud(GLfloat cx, GLfloat cy, GLfloat size) {
    glPushMatrix();
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

    glPopMatrix();
}


void drawCityBuildings() {

    glPushMatrix();  // isolate everything

    if(nightMode)
    glColor3f(0.20f, 0.20f, 0.25f);
else
    glColor3f(0.55f, 0.60f, 0.68f);

    // Base X position
    float x = -0.5f;

    // Building 1
    drawQuad(x, 0.0f, 0.1f, 0.20f);

    // Building 2
    x += 0.1f;
    glPushMatrix();
    glTranslatef(x + 0.5f, 0.0f, 0.0f);
    glScalef(1.0, 1.5, 1.0);
    drawQuad(-0.5f, 0.0f, 0.1f, 0.20f);
    glPopMatrix();

    // Building 3
    x += 0.1f;
    glPushMatrix();
    glTranslatef(x + 0.5f, 0.0f, 0.0f);
    glScalef(1.0, 0.7, 1.0);
    drawQuad(-0.5f, 0.0f, 0.08f, 0.20f);
    glPopMatrix();

    // Building 4
    x += 0.08f;
    glPushMatrix();
    glTranslatef(x + 0.5f, 0.0f, 0.0f);
    glScalef(1.0, 1.2, 1.0);
    drawQuad(-0.5f, 0.0f, 0.09f, 0.20f);
    glPopMatrix();

    // Building 5
    x += 0.09f;
    glPushMatrix();
    glTranslatef(x + 0.5f, 0.0f, 0.0f);
    glScalef(1.0, 2.0, 1.0);
    drawQuad(-0.5f, 0.0f, 0.1f, 0.20f);
    glPopMatrix();

    // Building 6
    x += 0.1f;
    glPushMatrix();
    glTranslatef(x + 0.5f, 0.0f, 0.0f);
    glScalef(1.0, 1.0, 1.0);
    drawQuad(-0.5f, 0.0f, 0.12f, 0.20f);
    glPopMatrix();

    // Building 7
    x += 0.12f;
    glPushMatrix();
    glTranslatef(x + 0.5f, 0.0f, 0.0f);
    glScalef(1.0, 1.3, 1.0);
    drawQuad(-0.5f, 0.0f, 0.1f, 0.20f);
    glPopMatrix();

    // Building 8
    x += 0.1f;
    glPushMatrix();
    glTranslatef(x + 0.5f, 0.0f, 0.0f);
    glScalef(1.0, 0.9, 1.0);
    drawQuad(-0.5f, 0.0f, 0.09f, 0.20f);
    glPopMatrix();

    // Building 9
    x += 0.09f;
    glPushMatrix();
    glTranslatef(x + 0.5f, 0.0f, 0.0f);
    glScalef(1.0, 0.7, 1.0);
    drawQuad(-0.5f, 0.0f, 0.08f, 0.20f);
    glPopMatrix();

    // Building 10
    x += 0.08f;
    glPushMatrix();
    glTranslatef(x + 0.5f, 0.0f, 0.0f);
    glScalef(1.0, 0.3, 1.0);
    drawQuad(-0.5f, 0.0f, 0.08f, 0.20f);
    glPopMatrix();

    glPopMatrix();
}



void drawGrass() {
    // Main grass area
   if(nightMode)
    glColor3f(0.10f, 0.35f, 0.10f);
else
    glColor3f(0.30f, 0.70f, 0.20f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 0.04f);
    glVertex2f(-1.0f, 0.04f);
    glEnd();


    if(nightMode)
    glColor3f(0.10f, 0.35f, 0.10f);
else
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
    glPushMatrix();
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

    glPopMatrix();

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
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
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
    glPopMatrix();
}


void drawBridge(){

    glColor3f(0.60f, 0.38f, 0.18f);

    glBegin(GL_QUADS);
    glVertex2f(-0.56, -0.14);
    glVertex2f(-0.30, -0.14);
    glVertex2f(-0.27, -0.093);
    glVertex2f(-0.525, -0.090);
    glEnd();

glColor3f(0.50f, 0.50f, 0.55f);
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

    glPushMatrix();  // START

    glColor3f(0.44f, 0.27f, 0.10f);

    glLineWidth(3.5f);
    glBegin(GL_LINES);
    glVertex2f(0.44f,-0.008f);
    glVertex2f(0.38f,-0.25f);
    glVertex2f(0.44f,-0.008f);
    glVertex2f(0.48f,-0.25f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.35f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.44f,-0.008f);
    glVertex2f(0.38f,-0.25f);
    glVertex2f(0.44f,-0.008f);
    glVertex2f(0.48f,-0.25f);
    glEnd();
    glPopMatrix();

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
    glPopMatrix();

}

void update(int v)
{
    if(planePosition > 1.0 && !rainMode && !nightMode)
        planePosition = -1.0f;

    planePosition = planePosition + planeSpeed;

	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
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

    glBegin(GL_POLYGON);
    glVertex2f(x - 0.09f, y);
    glVertex2f(x - 0.06f, y);
    glVertex2f(x - 0.068f, y + 0.067f);
    glVertex2f(x - 0.09f, y + 0.060f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x - 0.095f, y + 0.035f);
    glVertex2f(x - 0.055f, y + 0.038f);
    glVertex2f(x - 0.055f, y + 0.073f);
    glVertex2f(x - 0.095f, y + 0.07f);
    glEnd();

    glColor3f(0.55f, 0.82f, 0.97f);
    for (int i = 0; i < 5; i++)
        drawFilledCircle(x - 0.025f + i * 0.022f, y + 0.007f, 0.010f, 30);
}


void drawBench(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0.032f, -0.02f);
    glVertex2f(0.052f, -0.02f);
    glVertex2f(0.052f, 0.06f);
    glVertex2f(0.032f, 0.06f);

    glVertex2f(0.15f, -0.02f);
    glVertex2f(0.13f, -0.02f);
    glVertex2f(0.13f,  0.06f);
    glVertex2f(0.15f, 0.06f);
    glEnd();


    // Bench seat
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.18f, 0.0f);
    glVertex2f(0.18f, -0.03f);
    glVertex2f(0.0f, -0.03f);
    glEnd();

    // Backrest
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.05f);
    glVertex2f(0.18f, 0.05f);
    glVertex2f(0.18f, 0.02f);
    glVertex2f(0.0f, 0.02f);
    glEnd();

    // Legs
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0.01f, -0.03f);
    glVertex2f(0.03f, -0.03f);
    glVertex2f(0.03f, -0.08f);
    glVertex2f(0.01f, -0.08f);

    glVertex2f(0.15f, -0.03f);
    glVertex2f(0.17f, -0.03f);
    glVertex2f(0.17f, -0.08f);
    glVertex2f(0.15f, -0.08f);
    glEnd();
    glPopMatrix();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
if(nightMode)
{
    // Dark blue night sky
    glClearColor(0.05f, 0.05f, 0.12f, 1.0f);
}
else if(rainMode)
{
    // Rain sky
    glClearColor(0.25f, 0.25f, 0.32f, 1.0f);
}
else
{
    // Day sky
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
}



    drawSun();

    if(nightMode)
{
    drawStars();
}


    drawCloud(cloudPosition1, 0.82f, 0.055f);
    drawCloud(cloudPosition2, 0.65f, 0.055f);
    drawCloud(cloudPosition3,0.85f, 0.055f);

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

    drawRoundTree(0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(0,-0.2f,0);
    drawSwingSet();
    glPopMatrix();
    drawAirplane(planePosition, planeY);


    // Benches near the path
drawBench(-0.3f, 0.05f);
drawBench(0.3f, 0.05f);


    if (rainMode)
{
    glColor3f(0.75f, 0.75f, 1.0f);

    glLineWidth(1.2f);

    glBegin(GL_LINES);

    for (int i = 0; i < 600; i++)
    {
        rainDropY[i] -= 0.03f;

        // Reset rain drop
        if (rainDropY[i] < -1.0f)
        {
            rainDropY[i] = 1.0f;

            rainDropX[i] =
                ((rand() % 2000) / 1000.0f) - 1.0f;
        }

        glVertex2f(rainDropX[i], rainDropY[i]);

        glVertex2f(
            rainDropX[i] + 0.015f,
            rainDropY[i] - 0.05f
        );
    }

    glEnd();
}
    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(80, 50);
    glutCreateWindow("Park Scenario");
    init();
    initRain();
    glutDisplayFunc(display);
    glutTimerFunc(100, update, 0);
    glutTimerFunc(100, updateCloud, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialInput);
    glutMainLoop();

}









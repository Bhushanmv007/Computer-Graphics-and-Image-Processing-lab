#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>

int width = 800;
int height = 600;
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat scale = 1.0f;
int objectType = 0; // 0 for Tetrahedron, 1 for Cube

void drawTetra() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);

    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();
}

void drawCube() {
    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    glEnd();
}

void drawObject() {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -3.0f); // Translate the object back along Z-axis
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis
    glScalef(scale, scale, scale); // Scale the object
    if (objectType == 0)
        drawTetra();
    else
        drawCube();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW); // Switch to model-view matrix
    glLoadIdentity(); // Load identity matrix

    drawObject(); // Draw the selected object

    glutSwapBuffers(); // Swap the front and back buffers (double buffering)
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'x':
        rotationX += 5.0f;
        break;
    case 'X':
        rotationX -= 5.0f;
        break;
    case 'y':
        rotationY += 5.0f;
        break;
    case 'Y':
        rotationY -= 5.0f;
        break;
    case '+':
        scale += 0.1f;
        break;
    case '-':
        if (scale > 0.1f)
            scale -= 0.1f;
        break;
    case 27: // ASCII code for Escape key
        exit(0); // Exit the program
        break;
    }

    glutPostRedisplay(); // Mark the current window as needing to be redisplayed
}

void menu(int value) {
    objectType = value; // Set object type based on menu selection
    glutPostRedisplay(); // Mark the current window as needing to be redisplayed
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set display mode
    glutInitWindowSize(width, height); // Set initial window size
    glutCreateWindow("Geometric Operations in 3D"); // Create window with given title

    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set clear color to white

    glMatrixMode(GL_PROJECTION); // Switch to projection matrix
    glLoadIdentity(); // Load identity matrix
    gluPerspective(45.0f, (float)width / (float)height, 1.0f, 100.0f); // Set perspective projection

    glutCreateMenu(menu); // Create right-click context menu
    glutAddMenuEntry("Tetrahedron", 0); // Add menu entry for Tetrahedron
    glutAddMenuEntry("Cube", 1); // Add menu entry for Cube
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button

    glutDisplayFunc(display); // Set display callback function
    glutKeyboardFunc(keyboard); // Set keyboard callback function

    glutMainLoop(); // Enter GLUT event processing loop
    return 0;
}
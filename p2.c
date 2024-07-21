#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

GLfloat triangle[3][2] = {{0.0, 0.0}, {2.0, 0.0}, {1.0, 2.0}};

GLfloat tx = 3.0f, ty = 2.0f;
GLfloat angle = 45.0f;
GLfloat sx = 2.0f, sy = 0.5f;

void applyTransformations() {
    glScalef(sx, sy, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(tx, ty, 1.0f);
}

void display() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; ++i)
        glVertex2f(triangle[i][0], triangle[i][1]);
    glEnd();
    
    glPushMatrix();
    applyTransformations();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; ++i)
        glVertex2f(triangle[i][0], triangle[i][1]);
    glEnd();
    glPopMatrix();
    glFlush();
}

void myInit() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Geometric operations on 2D objects");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
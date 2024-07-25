#include <GL/glut.h>
#include <math.h>

const double TWO_PI = 6.2831853;
GLsizei winWidth = 500, winHeight = 500;
GLuint regHex;
static GLfloat rotTheta = 0.0;
GLint scrPtX, scrPtY;

void init(void) {
    GLdouble hexTheta;
    GLint k;
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    regHex = glGenLists(1); // Generate a display list
    glNewList(regHex, GL_COMPILE); // Start defining the display list
    glColor3f(1.0, 0.0, 0.0); // Set drawing color to red
    glBegin(GL_POLYGON); // Begin drawing filled polygon
    for (k = 0; k < 6; k++) { // Loop to specify each vertex of a hexagon
        hexTheta = TWO_PI / 6 * k; // Angle of hexagon vertex
        scrPtX = 150 + 100 * cos(hexTheta); // X-coordinate of hexagon vertex
        scrPtY = 150 + 100 * sin(hexTheta); // Y-coordinate of hexagon vertex
        glVertex2i(scrPtX, scrPtY); // Specify vertex of hexagon
    }
    glEnd(); // End drawing of hexagon
    glEndList(); // End definition of display list
}

void displayHex(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
    glPushMatrix(); // Save current modelview matrix
    glTranslatef(winWidth / 2, winHeight / 2, 0.0); // Translate to center of window
    glRotatef(rotTheta, 0.0, 0.0, 1.0); // Rotate about z axis
    glTranslatef(-winWidth / 2, -winHeight / 2, 0.0); // Translate back
    glCallList(regHex); // Execute display list to draw hexagon
    glPopMatrix(); // Restore previous modelview matrix
    glutSwapBuffers(); // Swap buffers for animation
}

void rotateHex(void) {
    rotTheta += 3.0; // Increment rotation angle
    if (rotTheta > 360.0)
        rotTheta -= 360.0; // Wrap around if angle exceeds 360 degrees
    glutPostRedisplay(); // Mark window for redisplay
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
    winWidth = newWidth; // Save new window width
    winHeight = newHeight; // Save new window height
    glViewport(0, 0, winWidth, winHeight); // Set viewport
    glMatrixMode(GL_PROJECTION); // Set matrix mode
    glLoadIdentity(); // Clear current matrix to identity matrix
    gluOrtho2D(0.0, winWidth, 0.0, winHeight); // Set orthographic projection
    glMatrixMode(GL_MODELVIEW); // Specify current matrix as modelview
    glLoadIdentity(); // Clear current matrix
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
}

void mouseFcn(GLint button, GLint action, GLint x, GLint y) {
    switch (button) {
        case GLUT_MIDDLE_BUTTON: // Middle mouse button pressed
            if (action == GLUT_DOWN)
                glutIdleFunc(rotateHex); // Start animation
            break;
        case GLUT_RIGHT_BUTTON: // Right mouse button pressed
            if (action == GLUT_DOWN)
                glutIdleFunc(NULL); // Stop animation
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set display mode
    glutInitWindowPosition(150, 150); // Set window position
    glutInitWindowSize(winWidth, winHeight); // Set window size
    glutCreateWindow("Animation Example"); // Create window with title
    init(); // Initialize drawing
    glutDisplayFunc(displayHex); // Set display callback function
    glutReshapeFunc(winReshapeFcn); // Set reshape callback function
    glutMouseFunc(mouseFcn); // Set mouse callback function
    glutMainLoop(); // Enter main event loop
    return 0;
}

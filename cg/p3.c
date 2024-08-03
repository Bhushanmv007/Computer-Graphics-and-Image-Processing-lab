#include <GL/glut.h>

void myInit() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);
}

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
        
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(-1.0, 1.0, -1.0);
        glVertex3f(1.0, -1.0, -1.0);
    glEnd();
}

void myDisplay() {
    drawTetra();
    glTranslatef(5.0, 6.0, 8.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(0.3, 0.3, 0.3);
    drawTetra();
    glFlush();
    glutSwapBuffers();
}

void myReshape(int w,int h){
    glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
	 	glOrtho(-2,2,-2*(GLfloat)h/(GLfloat)w,2*(GLfloat)h/(GLfloat)w,-10,10);
	else
	 	glOrtho(-2*(GLfloat)w/(GLfloat)h,2*(GLfloat)w/(GLfloat)h,-2,2,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int main(int argc,char**argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1200,1000);
	glutInitWindowPosition(10,10);
	glutCreateWindow("3D GEOMETRIC OPERATIONS");
	myInit();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}

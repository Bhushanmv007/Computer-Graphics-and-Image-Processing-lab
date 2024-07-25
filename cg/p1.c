#include <GL/glut.h>
#include <stdio.h>
int x1, Y1, x2, Y2;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_line(int x1, int x2, int Y1, int Y2) {
    int dx, dy, i, p, x, y, incx, incy, inc1, inc2;
    dx = x2 - x1;
    dy = Y2 - Y1;
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;

    incx = 1;
    if (x2 < x1)
        incx = -1;
    incy = 1;
    if (Y2 < Y1)
        incy = -1;
        
    x = x1;
    y = Y1;
    if (dx > dy) {
        draw_pixel(x, y);
        p = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++) {
            if (p >= 0) {
                y += incy;
                p += inc1;
            } else
                p += inc2;
            x += incx;
            draw_pixel(x, y);
        }
    } else {
        draw_pixel(x, y);
        p = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++) {
            if (p >= 0) {
                x += incx;
                p += inc1;
            } else
                p += inc2;
            y += incy;
            draw_pixel(x, y);
        }
    }
}

void myDisplay() {
    draw_line(x1, x2, Y1, Y2);
    glFlush();
}

int main(int argc, char **argv) {
    printf("enter(x1, x2, y1, y2)\n");
    scanf("%d %d %d %d", &x1, &x2, &Y1, &Y2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Line Drawing");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
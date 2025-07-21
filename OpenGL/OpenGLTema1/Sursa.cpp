#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

static GLfloat liquidLevel1 = 0.75;
static GLfloat liquidLevel2 = 0.25;
static int direction = 1;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void drawTank(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat level) {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x1, y1, 0.0);
    glVertex3f(x2, y1, 0.0);
    glVertex3f(x2, y2, 0.0);
    glVertex3f(x1, y2, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, 0.0);
    glVertex3f(x2, y1, 0.0);
    glVertex3f(x2, y1 + level * (y2 - y1), 0.0);
    glVertex3f(x1, y1 + level * (y2 - y1), 0.0);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    drawTank(0.1, 0.1, 0.4, 0.9, liquidLevel1);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(0.4, 0.10, 0.0);
    glVertex3f(0.6, 0.10, 0.0);
    glVertex3f(0.6, 0.20, 0.0);
    glVertex3f(0.4, 0.20, 0.0);
    glEnd();

    if (direction == 1) {
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glVertex3f(0.4, 0.10, 0.0);
        glVertex3f(0.4 + (liquidLevel2 - 0.25) / 0.5 * 0.2, 0.10, 0.0);
        glVertex3f(0.4 + (liquidLevel2 - 0.25) / 0.5 * 0.2, 0.20, 0.0);
        glVertex3f(0.4, 0.20, 0.0);
        glEnd();
    }
    else {
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glVertex3f(0.6 - (liquidLevel1 - 0.25) / 0.5 * 0.2, 0.10, 0.0);
        glVertex3f(0.6, 0.10, 0.0);
        glVertex3f(0.6, 0.20, 0.0);
        glVertex3f(0.6 - (liquidLevel1 - 0.25) / 0.5 * 0.2, 0.20, 0.0);
        glEnd();
    }

    drawTank(0.6, 0.1, 0.9, 0.9, liquidLevel2);

    glFlush();
    glutSwapBuffers();
}

void updateLiquidLevel(int value) {
    GLfloat step = 0.01;

    if (direction == 1) {
        liquidLevel1 -= step;
        liquidLevel2 += step;
        if (liquidLevel1 <= 0.25) {
            direction = -1;
        }
    }
    else {
        liquidLevel1 += step;
        liquidLevel2 -= step;
        if (liquidLevel1 >= 0.75) {
            direction = 1;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(100, updateLiquidLevel, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Liquid Transfer Animation");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100, updateLiquidLevel, 0);

    glutMainLoop();
    return 0;
}
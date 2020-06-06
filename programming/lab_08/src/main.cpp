#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Cube.hpp"
#include "display.hpp"

double rotate_y = 0;
double rotate_x = 0;
//float win_witdh = 800;
//float win_height = 800;
//int startTime;
//static GLfloat rot = 0.0f;
//static GLfloat rotRate = 45.0f;
rubiks_cube temp;

void specialKeys( int key, int x, int y ) {
    if (key == GLUT_KEY_RIGHT) rotate_y += 4;
    else if (key == GLUT_KEY_LEFT) rotate_y -= 4;
    else if (key == GLUT_KEY_UP) rotate_x += 4;
    else if (key == GLUT_KEY_DOWN) rotate_x -= 4;
    else if (key == GLUT_KEY_F1) temp.pif_paf();
    else if (key == GLUT_KEY_F2) temp.RIGHT();
    else if (key == GLUT_KEY_F3) temp.RIGHT_R();
    else if (key == GLUT_KEY_F4) temp.LEFT();
    else if (key == GLUT_KEY_F5) temp.LEFT_R();
    else if (key == GLUT_KEY_F6) temp.UP();
    else if (key == GLUT_KEY_F7) temp.UP_R();
    else if (key == GLUT_KEY_F8) temp.DOWN();
    else if (key == GLUT_KEY_F9) temp.DOWN_R();
    else if (key == GLUT_KEY_F10) temp.CLOCK_L();
    else if (key == GLUT_KEY_F11) temp.CLOCK_R();
    else if (key == GLUT_KEY_F12) temp.all_left();
    glutPostRedisplay();
}

void display() {
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
//    glRotatef(rot, 0.0, 1.0, 0);
    glScalef(0.2, 0.2, 0.2);
    temp.draw();
    glFlush();
    glutSwapBuffers();
}

//void animate() {
//    int currTime = glutGet(GLUT_ELAPSED_TIME);
//    int elapsedTime = currTime - startTime;
//    rot = (rotRate / 1000) * elapsedTime;
//    glutPostRedisplay();
//}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(GLUT_INIT_WINDOW_WIDTH / 2, GLUT_INIT_WINDOW_HEIGHT / 2);
    glutCreateWindow("Custom Rubik's Cube");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
//    glutIdleFunc(animate);
//    startTime = glutGet(GLUT_ELAPSED_TIME);
    glutMainLoop();
    std::cout << "==========Shutting down==========\n";
    return 0;
}

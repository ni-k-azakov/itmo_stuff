#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Board.hpp"
#include "display.hpp"
#include "Enums.hpp"
#include "Player.hpp"

double rotate_y = 0;
double rotate_x = 0;

Board temp_board;

Player actual_player(&temp_board);
//Player black_player;
//Player &actual_player = white_player;

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) rotate_y += 4;
    else if (key == GLUT_KEY_LEFT) rotate_y -= 4;
    else if (key == GLUT_KEY_UP) rotate_x += 4;
    else if (key == GLUT_KEY_DOWN) rotate_x -= 4;
    else if (key == GLUT_KEY_SHIFT_L) {
        std::cout << "==========Shutting down==========\n";
        exit(EXIT_SUCCESS);
    }
    glutPostRedisplay();
}

void simpleKeys(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'W') actual_player.change_pos(up);
    else if (key == 'a' || key == 'A') actual_player.change_pos(left);
    else if (key == 's' || key == 'S') actual_player.change_pos(down);
    else if (key == 'd' || key == 'D') actual_player.change_pos(right);
    else if (key == ' ') actual_player.pick();
    glutPostRedisplay();
}
void display() {
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glScalef(0.7, 0.7, 0.7);
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glScalef(0.2, 0.2, 0.2);
    temp_board.draw();
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(GLUT_INIT_WINDOW_WIDTH / 2, GLUT_INIT_WINDOW_HEIGHT / 2);
    glutCreateWindow("Custom Chess");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(simpleKeys);
    glutMainLoop();
    return 0;
}

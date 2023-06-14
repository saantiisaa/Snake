#include <GL/glut.h>
#include <vector>
#include <Windows.h>
#include <iostream>

#include "Scene.h"

using namespace gameSnake;

Scene* scene;

void on_timer(int value)
{
    scene->logic();
    scene->draw();

    scene->tick++;
    if (scene->tick >= 4) // нарахували наступну секунду
    {
        if (!scene->gameOver)// секунди нарощуються, якщо гру не закінчено
        {
            scene->timer++;
        }
        scene->tick = 0;   // скинули лічильник
    }
    scene->draw();     // здійснюємо перемалювання вікна

    glutTimerFunc(200, on_timer, 0);
}

void draw() { scene->draw(); }
void onSpecialKeys(int key, int x, int y) { scene->onSpecialKeys(key, x, y); }
void on_keyboard(unsigned char key, int x, int y) { scene->on_keyboard(key, x, y); }

int main(int argc, char** argv)
{
    scene = new Scene();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(1000, 800);
    glutCreateWindow("GLUT");

    scene->init();

    glutDisplayFunc(draw);
    glutSpecialFunc(onSpecialKeys);
    glutKeyboardFunc(on_keyboard);
    glutTimerFunc(200, on_timer, 0);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

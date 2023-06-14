#include "Scene.h"

#include <GL/glut.h>
#include <vector>
#include <Windows.h>
#include <iostream>

using namespace std;

namespace gameSnake
{
    void Scene::init()
    {
        extreamX = 7;
        extreamY = 7;
        extreamZ = 7;

        gameOver = false;
        score = 0;
        timer = 0;

        headShiftX = 0;
        headShiftY = 2;
        headShiftZ = 0;

        srand((unsigned)time(0));
        fruitShiftX = generateRandomShift(14); //fruit shift can be -14, -12, ..., 0, 2, ..., 14.
        fruitShiftY = 2;
        fruitShiftZ = generateRandomShift(14);

        direction = Direction::UP;

        vector<Segment> newSegments;
        segments = newSegments;
    }

    void Scene::restart()
    {
        init();
    }

    float** Scene::createShiftedCubeMatrix8x3(float** matrix, float shiftX, float shiftY, float shiftZ)
    {
        float** newMatrix;
        newMatrix = new float* [8];
        for (int i = 0; i < 8; i++)
        {
            newMatrix[i] = new float[3];
            newMatrix[i][0] = matrix[i][0] + shiftX;
            newMatrix[i][1] = matrix[i][1] + shiftY;
            newMatrix[i][2] = matrix[i][2] + shiftZ;
        }
        return newMatrix;
    }

    void Scene::createAndDrawCube(float** matrixVertices)
    {
        Cube* cube = new Cube(matrixVertices);
        cube->draw();
        delete cube;
    }

    void Scene::drawHead(float** m)
    {
        glColor3f(1, 0.1, 0.7);
        createAndDrawCube(m);
    }

    void Scene::drawSegment(float** segmentMatrix)
    {
        glColor3f(1, 0.2, 0.8);
        createAndDrawCube(segmentMatrix);
    }

    void Scene::drawFruit()
    {
        float** fruitMatrix = createShiftedCubeMatrix8x3(startCubeVertices, fruitShiftX, fruitShiftY, fruitShiftZ);
        glColor3f(0.8, 0.8, 0.2);
        createAndDrawCube(fruitMatrix);
    }

    void Scene::drawFieldCubes()
    {
        Cube* cube = new Cube(NULL);// refactor to static
        startCubeVertices = cube->getBaseMatrix();

        for (int x = -extreamX; x <= extreamX; x++)
        {
            for (int z = -extreamZ; z <= extreamZ; z++)
            {
                float** cubeMatrix = createShiftedCubeMatrix8x3(startCubeVertices, x * 2, 0, z * 2);
                Cube* cube = new Cube(cubeMatrix);
                glColor3f(0, 0.8, 0.6);
                cube->draw();
                delete cube;
            }
        }
    }

    void Scene::onSpecialKeys(int key, int x, int y)
    {
        if (key == GLUT_KEY_RIGHT)
            rotate_y += 5;
        else if (key == GLUT_KEY_LEFT)
            rotate_y -= 5;
        else if (key == GLUT_KEY_UP)
            rotate_x += 5;
        else if (key == GLUT_KEY_DOWN)
            rotate_x -= 5;
        else if (key == GLUT_KEY_F2)
        {
            restart();
        }
        glutPostRedisplay();
    }

    void Scene::drawString(void* font, const char* text, float x, float y)
    {
        if (!text) // нульовий указівник
        {
            return;
        }
        // Встановлення позиції тексту:
        glRasterPos2f(x, y);
        while (*text)
        {
            // Рядок виводиться посимвольно:
            glutBitmapCharacter(font, *text);
            text++;
        }
    }

    void Scene::drawTitleText()
    {
        char text[128];
        if (!gameOver)
        {
            sprintf_s(text, "A, W, D, S - Change direction      ARROWS - Change camera      Score: %d           Time: %d s ", score, timer);
        }
        else
            sprintf_s(text, "GAME OVER      FINAL SCORE - %d    TIME - %d s      F2 - Restart", score, timer);

        // Очищуємо буфери:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0, 1, 0, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1, 0.1, 0.5); // жовтий текст
        drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
        glPopMatrix();

        // Включаємо режим роботи з матрицею проекцій:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
    }

    void Scene::draw2D()
    {
        drawTitleText();
    }

    void Scene::draw3D()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        int w = glutGet(GLUT_WINDOW_WIDTH);
        int h = glutGet(GLUT_WINDOW_HEIGHT);

        gluPerspective(70, w / h, 0.1, 100);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt
        (
            -25, 22, 0,
            0, 0, 0,
            0, 3, 0
        );

        glRotatef(rotate_x, 1.0, 0.0, 0.0);
        glRotatef(rotate_y, 0.0, 1.0, 0.0);

        drawFieldCubes();
        headMatrix = createShiftedCubeMatrix8x3(startCubeVertices, headShiftX, headShiftY, headShiftZ);
        drawHead(headMatrix);
        for (Segment segment : segments)
        {
            float** segmentMatrix = createShiftedCubeMatrix8x3(startCubeVertices, segment.x, segment.y, segment.z);
            drawSegment(segmentMatrix);
        }
        drawFruit();

        glutSwapBuffers();
    }

    void Scene::draw()
    {
        if (!gameOver)
        {
            glClearColor(0, 0.8, 0.9, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else
        {
            glClearColor(0, 0.75, 0.9, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        draw2D();
        draw3D();
    }

    void Scene::on_keyboard(unsigned char key, int x, int y)
    {
        // Обробка подій від клавіатури:
        switch (key)
        {
        case 'w':

            if (direction != DOWN)
                direction = UP;
            break;
        case 'd':

            if (direction != LEFT)
                direction = RIGHT;
            break;
        case 's':

            if (direction != UP)
                direction = DOWN;
            break;
        case 'a':

            if (direction != RIGHT)
                direction = LEFT;
            break;
        }
    }

    void Scene::logic()
    {
        if (gameOver)
            return;

        // Move head
        Segment prevPosition(headShiftX, headShiftY, headShiftZ);
        if (direction == Direction::UP)
        {
            if (headShiftX == extreamX * 2)
                headShiftX = -headShiftX;
            else
                headShiftX += 2;
        }
        else if (direction == Direction::RIGHT)
        {
            if (headShiftZ == extreamZ * 2)
                headShiftZ = -headShiftZ;
            else
                headShiftZ += 2;
        }
        else if (direction == Direction::DOWN)
        {
            if (headShiftX == -extreamX * 2)
                headShiftX = -headShiftX;
            else
                headShiftX -= 2;
        }
        else if (direction == Direction::LEFT)
        {
            if (headShiftZ == -extreamZ * 2)
                headShiftZ = -headShiftZ;
            else
                headShiftZ -= 2;
        }

        // Check meet tail
        for (Segment segment : segments)
        {
            if (headShiftX == segment.x && headShiftY == segment.y && headShiftZ == segment.z)
            {
                gameOver = true;
            }
        }

        // Move segments
        Segment bufferedSegment;
        for (int i = 0; i < segments.size(); i++)
        {
            Segment buffer(segments[i].x, segments[i].y, segments[i].z);
            segments[i].x = prevPosition.x;
            segments[i].y = prevPosition.y;
            segments[i].z = prevPosition.z;
            prevPosition = buffer;
        }

        // Check meet fruit
        if (headShiftX == fruitShiftX && headShiftY == fruitShiftY && headShiftZ == fruitShiftZ)
        {
            fruitShiftX = generateRandomShift(extreamX * 2);
            fruitShiftZ = generateRandomShift(extreamZ * 2);

            Segment segment(headShiftX, headShiftY, headShiftZ);
            segments.push_back(segment);

            score++;
        }
    }
}
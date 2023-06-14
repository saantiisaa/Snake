#include "Cube.h"

#include <GL/glut.h>
#include <Windows.h>

namespace gameSnake
{
    int generateRandomShift(int border)
    {
        int halfBorder = border / 2;
        int num = ((rand() % (halfBorder + 1 + halfBorder)) - halfBorder) * 2;
        return num;
    }

    float** convertArray8x3(float staticArray[8][3])
    {
        int size = 8;
        float** dynamicArray = new float* [size];
        for (int i = 0; i < size; i++)
        {
            dynamicArray[i] = new float[3]{ staticArray[i][0], staticArray[i][1], staticArray[i][2] };
        }
        return dynamicArray;
    }

    void Cube::drawQuadrangle(float** matrix, int a, int b, int c, int d)
    {
        glBegin(GL_QUADS);
        glVertex3fv(matrix[a]);
        glVertex3fv(matrix[b]);
        glVertex3fv(matrix[c]);
        glVertex3fv(matrix[d]);
        glEnd();
    }

    void Cube::drawCube(float** vertices)
    {
        drawQuadrangle(vertices, 0, 1, 2, 3);// front
        drawQuadrangle(vertices, 4, 5, 6, 7);// back
        drawQuadrangle(vertices, 1, 5, 6, 2);// up
        drawQuadrangle(vertices, 2, 6, 7, 3);// right
        drawQuadrangle(vertices, 0, 4, 7, 3);// down
        drawQuadrangle(vertices, 0, 1, 5, 4);// left
    }

    Cube::Cube(float** matrixVertices)
    {
        this->matrixVertices = matrixVertices;
    }

    float** Cube::getBaseMatrix()
    {
        return convertArray8x3(cubeVertices);
    }

    void Cube::draw()
    {
        drawCube(matrixVertices);
    }
}
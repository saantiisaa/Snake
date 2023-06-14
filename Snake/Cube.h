#ifndef Cube_h
#define Cube_h

#include "Shape.h"

namespace gameSnake
{
    int generateRandomShift(int border);

    float** convertArray8x3(float staticArray[8][3]);

    class Cube : Shape
    {
    private:
        float cubeVertices[8][3] =
        {
            { -1 , -1 , 1 },// front left bottom 
            { -1 ,  1 , 1 },// front left up
            {  1 ,  1 , 1 },// front right up
            {  1 , -1 , 1 },// front right bottom
            { -1 , -1 ,-1 },// back left bottom
            { -1 ,  1 ,-1 },// back left up
            {  1 ,  1 ,-1 },// back right up
            {  1 , -1 ,-1 },// back right bottom
        };

        float** matrixVertices;

        void drawQuadrangle(float** matrix, int a, int b, int c, int d);

        void drawCube(float** vertices);

    public:
        Cube(float** matrixVertices);
        float** getBaseMatrix();
        void draw();
    };
}
#endif
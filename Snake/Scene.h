#ifndef Scene_h
#define Scene_h

#include <GL/glut.h>
#include <vector>
#include <Windows.h>
#include <iostream>

#include "Cube.h"
#include "Direction.h"

using namespace std;

namespace gameSnake
{
    struct Segment
    {
        float x;
        float y;
        float z;

        Segment(float x = 0, float y = 0, float z = 0)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

    class Scene
    {
    public:
        float** headMatrix;
        float** startCubeVertices;

        int extreamX;
        int extreamY;
        int extreamZ;

        int headShiftX;
        int headShiftY;
        int headShiftZ;

        int fruitShiftX; 
        int fruitShiftY;
        int fruitShiftZ;

        int score;
        bool gameOver;

        Direction direction;

        vector<Segment> segments;

        int tick = 0;
        int timer = 0;

        Scene() {}

        void init();
        void restart();
        float** createShiftedCubeMatrix8x3(float** matrix, float shiftX, float shiftY, float shiftZ);
        void createAndDrawCube(float** matrixVertices);
        void drawHead(float** m);
        void drawSegment(float** segmentMatrix);
        void drawFruit();
        void drawFieldCubes();
        double rotate_y = 0;
        double rotate_x = 0;

        void onSpecialKeys(int key, int x, int y);
        void drawString(void* font, const char* text, float x, float y);
        void drawTitleText();
        void draw2D();
        void draw3D();
        void draw();
        void on_keyboard(unsigned char key, int x, int y);
        void logic();
    };

};


#endif
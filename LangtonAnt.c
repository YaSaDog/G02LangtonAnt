#include <stdlib.h>

#include "glut.h"
#include "LangtonAnt.h"

void SetCell(byte* F, int x, int y, int value)
{
    x = (x + W) % W;
    y = (y + H) % H;

    F[y * W + x] = value;
}

int GetCell(byte* F, int x, int y)
{
    x = (x + W) % W;
    y = (y + H) % H;

    return F[y * W + x];
}


void InitFrame(byte* F)
{
    int x, y;
    for (y = 0; y < H; y++)
        for (x = 0; x < W; x++)
            F[y * W + x] = 0;
}

void InitVector(MotionVector *vect, int dx, int dy)
{
    vect->dx = dx;
    vect->dy = dy;
}

void InitAnt(Ant *ant, int x, int y, int dx, int dy)
{
    ant->x = (x + W) % W;
    ant->y = (y + H) % H;
    MotionVector *v = &(ant->motionVect);
    InitVector(v, dx, dy);
}

void MoveAnt(Ant *ant, byte* F)
{
    int x = ant->x, y = ant->y,
        dx = ant->motionVect.dx,
        dy = ant->motionVect.dy;

    if (GetCell(F, x, y) == 0) //black => turning left
    {
        if (dx == 0 && dy == -1) //up
            dx = -1, dy = 0;
        else if (dx == -1 && dy == 0) //left
            dx = 0, dy = 1;
        else if (dx == 0 && dy == 1) // down
            dx = 1, dy = 0;
        else if (dx == 1 && dy == 0) // right
            dx = 0, dy = -1;

        SetCell(F, x, y, 1);
    }
    else if (GetCell(F, x, y) == 1) //white => turning right
    {
        if (dx == 0 && dy == -1) //up
            dx = 1, dy = 0;
        else if (dx == -1 && dy == 0) //left
            dx = 0, dy = -1;
        else if (dx == 0 && dy == 1) // down
            dx = -1, dy = 0;
        else if (dx == 1 && dy == 0) // right
            dx = 0, dy = 1;

        SetCell(F, x, y, 0);
    }

    ant->motionVect.dx = dx;
    ant->motionVect.dy = dy;

    ant->x = (x + dx + W) % W;
    ant->y = (y + dy + H) % H;
}

void DrawFrame(byte* F, int antX, int antY)
{
    int x, y;

    for (y = 0; y < H; y++)
        for (x = 0; x < W; x++)
        {
            if (F[y * W + x] == 0)
                PutPixel(x, y, 0, 0, 0);
            else if (F[y * W + x] == 1)
                PutPixel(x, y, 255, 255, 255);

            if (x == antX && y == antY)
                PutPixel(x, y, ANT_R, ANT_G, ANT_B);
        }
}
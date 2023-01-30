#include <stdlib.h>

#include "glut.h"
#include "LangtonAnt.h"

byte Frame[H][W][3];
byte* F;

byte fullscreen = 0;
float Zoom = 1;
double rasterX = -1, rasterY = -1;

Ant *ant;

void PutPixel(int x, int y, int r, int g, int b)
{
    if (x < W && y < H)
    {
        Frame[y][x][0] = b;
        Frame[y][x][1] = g;
        Frame[y][x][2] = r;
    }
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    DrawFrame(F, ant->x, ant->y);
    MoveAnt(ant, F);

    glPixelZoom(Zoom, Zoom);
    glDrawPixels(W, H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

    glFinish();
    glutSwapBuffers();
    glutPostRedisplay();
}
void Keyboard(byte key, int x, int y)
{
    switch (key)
    {
    case '+':
        Zoom += 0.2;
        break;
    case '-':
        Zoom -= 0.2;
        break;
    case 'w':
        rasterY += 0.1;
        glRasterPos2d(rasterX, rasterY);
        break;
    case 'a':
        rasterX -= 0.1;
        glRasterPos2d(rasterX, rasterY);
        break;
    case 's':
        rasterY -= 0.1;
        glRasterPos2d(rasterX, rasterY);
        break;
    case 'd':
        rasterX += 0.1;
        glRasterPos2d(rasterX, rasterY);
        break;
    case 'f':
        if (fullscreen == 0)
        {
            glutFullScreen();
            fullscreen = 1;
        }
        else
        {
            glutReshapeWindow(WIN_W, WIN_H);
            glutPositionWindow(0, 0);
            fullscreen = 0;
        }
        break;
    case 27: //escape
        free(F);
        free(ant);
        exit(0);
    case 'r':
        InitAnt(ant, W / 2, H / 2, 0, -1);
        InitFrame(F);
        break;
    }
}


int main(int argc, char* argv[])
{
    if ((ant = malloc(sizeof(Ant))) == NULL)
        return;
    InitAnt(ant, W / 2, H / 2, 0, -1);

    if ((F = malloc(W * H)) == NULL)
        return;
    InitFrame(F);

    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(10, 10);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Langton's Ant");

    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);

    glClearColor(0.1, 0.2, 0.2, 1);

    glutMainLoop();
   
    free(F);
    free(ant);
    return 0;
}
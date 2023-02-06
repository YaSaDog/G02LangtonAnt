typedef unsigned char byte;

#define W 500
#define H 500
#define WIN_W 600
#define WIN_H 600
#define ANT_R 255
#define ANT_G 0
#define ANT_B 0

typedef struct MotionVector
{
    int dx, dy;
} MotionVector;

typedef struct Ant
{
    int x, y;
    struct MotionVector motionVect;
} Ant;

void PutPixel(int x, int y, int r, int g, int b);

void SetCell(byte* F, int x, int y, int value);
int GetCell(byte* F, int x, int y);

void InitFrame(byte* F);
void InitVector(MotionVector* vect, int dx, int dy);
void InitAnt(Ant* ant, int x, int y, int dx, int dy);

void MoveAnt(Ant* ant, byte* F);
void DrawFrame(byte* F, int antX, int antY);
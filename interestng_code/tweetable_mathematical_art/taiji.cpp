// NOTE: compile with g++ filename.cpp -std=c++11

#include <iostream>
#include <cmath>
#include <cstdlib>
#define DIM 1024
#define DM1 (DIM - 1)
#define _sq(x) ((x) * (x))                          // square
#define _cb(x) abs((x) * (x) * (x))                 // absolute value of cube
#define _cr(x) (unsigned char)(pow((x), 1.0 / 3.0)) // cube root

unsigned char GR(int, int);
unsigned char BL(int, int);

unsigned char RD(int i, int j)
{
  // YOUR CODE HERE
#define LEFT (i < DIM / 2)
#define C1 C(DIM / 2, DIM / 2, DIM / 2)
#define C2 C(DIM / 2, DIM / 4, DIM / 4)
  return BL(i, j);
}
unsigned char GR(int i, int j)
{
  // YOUR CODE HERE
#define C3 C(DIM / 2, 3 * DIM / 4, DIM / 4)
#define C4 C(DIM / 2, DIM / 4, DIM / 16)
#define C5 C(DIM / 2, 3 * DIM / 4, DIM / 16)
  return BL(i, j);
}
unsigned char BL(int i, int j)
{
  // YOUR CODE HERE
#define C(x, y, r) (_sq(i - (x)) + _sq(j - (y)) < _sq((r)))
  return !C1 ? 127 : C2 ? C4 ? 0 : 255 : C3 ? C5 ? 255 : 0 : LEFT ? 255 : 0;
}

void pixel_write(int, int);
FILE *fp;

int main()
{
  fp = fopen("MathPic.ppm", "wb");
  fprintf(fp, "P6\n%d %d\n255\n", DIM, DIM);
  for (int j = 0; j < DIM; j++)
    for (int i = 0; i < DIM; i++)
      pixel_write(i, j);

  fclose(fp);
  return 0;
}

void pixel_write(int i, int j)
{
  static unsigned char color[3];
  color[0] = RD(i, j) & 255;
  color[1] = GR(i, j) & 255;
  color[2] = BL(i, j) & 255;
  fwrite(color, 1, 3, fp);
}
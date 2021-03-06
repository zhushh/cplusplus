// NOTE: compile with g++ filename.cpp -std=c++11

#include <ctime>

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
  // return rand() + 63;

  double a = 0, b = 0, d, n = 0;
  for (; a * a + (d = b * b) < 4 && n++ < 8192; b = 2 * a * b + j / 5e4 + .06, a = a * a - d + i / 5e4 + .34)
    ;
  return n / 4;
}
unsigned char GR(int i, int j)
{
  return 3 * RD(i, j);
}
unsigned char BL(int i, int j)
{
  return 6 * RD(i, j);
}

void pixel_write(int, int);
FILE *fp;

int main()
{
  srand(time(NULL));

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

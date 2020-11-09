// NOTE: compile with g++ filename.cpp -std=c++11

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#define DIM 1024
#define DM1 (DIM - 1)
#define _sq(x) ((x) * (x))                          // square
#define _cb(x) abs((x) * (x) * (x))                 // absolute value of cube
#define _cr(x) (unsigned char)(pow((x), 1.0 / 3.0)) // cube root

unsigned char GR(int, int);
unsigned char BL(int, int);

unsigned char RD(int i, int j)
{
#define g(S) (S[i / 29 % 18 * 2 + j / 29 / 8 % 2] >> j / 29 % 8 & 1) * DM1 *(abs(i - 512) < 247 & abs(j - 464) < 232)
  return g("\xF3\xF2\xF2\x10\xF4\0\xF2\x10\xE1\xE0\x81\0\x80\0\x80\0\0\0\0\0@\0! \x03d8,=\x2C\x99\x84\xC3\x82\xE1\xE3");
}

unsigned char GR(int i, int j)
{
  return g(";\376z\34\377\374\372\30k\360\3\200\0\0\0\0\0\0\200\0\300\0\341 \373d\307\354\303\374e\374;\376;\377") ? DM1 : BL(i, j) ? DM1 / 2 : 0;
}

unsigned char BL(int i, int j)
{
  return g("\363\360\362\20\364\0\362\20\341\340\200\0\200\0\200\0\0\0\0\0\0\0\0\0\0\08\0<\0\230\0\300\0\341\340") / 2;
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

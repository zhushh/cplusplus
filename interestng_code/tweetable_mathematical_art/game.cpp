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
#define g(I, S, W, M) j / 128 % 8 == I &W >> (j / 32 % 4 * 16 + i / 64) % M &S[abs(i / 4 % 16 - 8) - (I % 2 & i % 64 < 32)] >> j / 4 % 8 & 1
  return g(1, "_\xB6\\\x98\0\0\0", 255L << 36, 64) ? j : 0;
}

unsigned char GR(int i, int j)
{
#define S g(6, "\xFF\xFE\xF8\xF8\xF8\xF8\xF0\x0", 1L << 22, 64) | i / 4 == 104 & j / 24 == 30
  return g(2, "<\xBC\xB6}\30p\0\0", 4080, 32) | S ? j : 0;
}

unsigned char BL(int i, int j)
{
  return g(3, "_7\xB6\xFE\x5E\34\0", 0x70000000FD0, 64) | S | abs(i / 4 - 128) == 80 & abs(j / 4 - 128) < 96 | abs(j / 4 - 128) == 96 & abs(i / 4 - 128) < 80 ? j : 0;
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

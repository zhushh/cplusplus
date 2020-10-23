## Tweetable Mathematical Art
替换**RD**、 **GR**和**BL**三个函数的实现，然后生成一个1024x1024大小的图片

代码框架：`painting.cpp`
```c++
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
}
unsigned char GR(int i, int j)
{
  // YOUR CODE HERE
}
unsigned char BL(int i, int j)
{
  // YOUR CODE HERE
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
```

链接：[https://codegolf.stackexchange.com/questions/35569/tweetable-mathematical-art](https://codegolf.stackexchange.com/questions/35569/tweetable-mathematical-art)

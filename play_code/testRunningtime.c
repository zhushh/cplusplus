#include <stdio.h>
#include <time.h>

// clock 获取CPU运行的时钟周期计数
int main() {
    clock_t start, finish;
    int i, sum = 0;
    start = clock();
    for (i = 0; i < 100; i++) {
        sum += i;
    }
//    printf("%d\n", sum);
    finish = clock();
    printf("Running time == %lf seconds\n", (double)(finish - start)/CLOCKS_PER_SEC);
    return 0;
}


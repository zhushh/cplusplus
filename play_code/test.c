#include <stdio.h>
#include <time.h>

#define TIME
#define MAX 10000000
int arr[MAX * 2] = {0};

int main() {
    int n, k, i, num, max = -10000001;
    clock_t start, finish;
    scanf("%d", &n);
    scanf("%d", &k);
    for (i = 0; i < n; i++) {
        scanf("%d", &num);
        arr[num + MAX] = 1;
        max = max > num ? max : num;
    }
    start = clock();
    for (i = max + MAX; k > 0; i--) {
        if (1 == arr[i]) k--;
    }
#ifdef TIME
    printf("%d\n", i + 1 - MAX);
    finish = clock();
    printf("Running time = %.4lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
#endif
    return 0;
}

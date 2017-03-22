#include <stdio.h>
#include <stdlib.h>

// void qsort(void *array, size_t nmemb, size_t size,
//               int (*compare)(const void*, const void*));
int cmp(const void *a, const void *b) {
    int *numa = (int*)a;
    int *numb = (int*)b;
    return *numa - *numb;
}
int main() {
    int a[6] = {12, 3, 45, 6, 7, 10};
    int i;
    for (i = 0; i < 6; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    qsort(a, 6, sizeof(int), cmp);
    for (i = 0; i < 6; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}


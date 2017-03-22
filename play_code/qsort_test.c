#include <stdio.h>

#define max 100

void qsort(int *arr, int low, int hig);
int main() {
    int num, a[max], i;
    scanf("%d", &num);
    for (i = 0; i < num; ++i) {
        scanf("%d", &a[i]);
    }
    qsort(a, 0, num - 1);
    for (i = 0; i < num; ++i) {
        printf("%d", a[i]);
        if (i < num - 1) printf(" ");
        else printf("\n");
    }
    return 0;
}
void qsort(int *arr, int low, int hig) {
    if (low < hig) {
        int l = low, h = hig, key = arr[low];
        while (l < h) {
            while (l < h && arr[h] < key) --h;
            if (l < h) arr[l++] = arr[h];
            while (l < h && arr[l] >= key) ++l;
            if (l < h) arr[h--] = arr[l];
        }
        arr[l] = key;
        qsort(arr, low, l - 1);
        qsort(arr, l + 1, hig);
    }
}


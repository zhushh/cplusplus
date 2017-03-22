#include <stdio.h>
#include <time.h>

#define MAX 10000000
int arr[MAX * 2] = {0};

void quick_sort(int *start, int *end) {
    if (start < end) {
        int * low = start, * high = --end, temp = *start;
        while (low != high) {
            while (low != high && *high < temp) --high;
            if (low != high) *low++ = *high;
            while (low != high && *low > temp) ++low;
            if (low != high) *high-- = *low;
        }
        *low-- = temp;
        quick_sort(start, low++);
        quick_sort(++low, ++end);
    }
}

int main() {
    int n, k, i;
/*    clock_t start, finished; */
    scanf("%d", &n);
    scanf("%d", &k);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
/*    start = clock(); */
    quick_sort(arr, arr + n);
    for (i = 1; i < n && k > 1; i++) {
        if (arr[i] != arr[i - 1]) {
            k--;
        } else if (arr[i] == arr[0]) {
            k--;
        }
    }
/*    finished = clock(); */
    printf("%d\n", arr[i - 1]);

/* #ifdef TIME */
/*    printf("Runnig time = %.4lf\n", (double)(finished - start)/CLOCKS_PER_SEC); */
/* #endif*/
    return 0;
}


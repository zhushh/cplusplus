#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100
#define max_length 100

void string_qsort(char (*s)[], int low, int hig);
int main() {
    int n, i;
    char str[max][max_length];
    scanf("%d", &n);
    getchar();
    for (i = 0; i < n; ++i) {
        gets(str[i]);
    }
    string_qsort(str, 0, n - 1);
    for (i = 0; i < n; ++i)
        printf("%s\n", str[i]);
    return 0;
}
void string_qsort(char (*s)[], int low, int hig) {
    if (low < hig) {
       int l = low, h = hig;
       char temp[max_length];
       strncpy(temp, s[low], max_length);
       while (l < h) {
           while (l < h && strcmp(s[h], temp) < 0) --h;
           if (l < h) strncpy(s[l++], s[h], max_length);
           while (l < h && strcmp(s[l], temp) >= 0) ++l;
           if (l < h) strncpy(s[h--], s[l], max_length);
       }
       strncpy(s[l], temp, max_length);
       qsort(s, low, l - 1);
       qsort(s, l + 1, hig);
    }
}


#include <stdio.h>
#define MAX 100

int main() {
    int i;
    char str1[MAX], str2[MAX];
    printf("Input string:\n");
    fgets(str1, sizeof(str1), stdin);
    for (i = 0; str1[i] != '\n' && i < MAX - 1; ++i) {
        str2[i] = str1[i];
    }
    str2[i] = '\0';
    printf("%s\n", str2);
    return 0;
}


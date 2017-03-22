#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main() {
    int i, len_a, len_b;
    char str_a[100], str_b[100];
    char *str;
    printf("Input string a:\n");
    fgets(str_a, sizeof(str_a), stdin);
    printf("Input string b:\n");
    fgets(str_b, sizeof(str_b), stdin);
    for (len_a = 0; str_a[len_a] != '\n'; ++len_a);
    str_a[len_a] = '\0';
    for (len_b = 0; str_b[len_b] != '\n'; ++len_b);
    str_b[len_b] = '\0';
    str = (char *)malloc(sizeof(char)*(len_a + len_b));
    memset(str, 0, sizeof(str));
    for (i = 0; i < len_a; ++i) str[i] = str_a[i];
    for (; i <= len_a + len_b; ++i) str[i] = str_b[i - len_a];
    printf("string a + b:\n");
    printf("%s\n", str);
    free(str);
    return 0;
}



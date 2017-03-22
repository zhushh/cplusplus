#include <stdio.h>

int main() {
    int i, len;
    char str1[100], str[100];
    printf("Input string:\n");
    fgets(str1, sizeof(str1), stdin);
    for (len = 0; str1[len] != '\n'; ++len);
    str1[len] = '\0';
    for (i = 0; i <= len; ++i) str[i] = str1[i];
    printf("The copy string:\n%s\n", str);
    return 0;
}



#include <stdio.h>
#include <string.h>

// char *index(const char *s, int c);
int main() {
    char str[100], ch;
    fgets(str, sizeof(str), stdin);
    scanf("%c", &ch);
    char *p = index(str, ch);
    printf("%s\n", p);
    return 0;
}


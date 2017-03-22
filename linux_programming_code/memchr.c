#include <stdio.h>
#include <string.h>

// void *memchr(void *s, int c, size_t n);
int main() {
    char str[100];
    char ch;
    fgets(str, sizeof(str), stdin);
    scanf("%c", &ch);
    char *p = memchr(str, ch, sizeof(str));
    printf("%s\n", p);
    return 0;
}


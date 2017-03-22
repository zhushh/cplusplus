#include <stdio.h>
#include <string.h>

// int strncasecmp(const char *s1, const char *s2, size_t n);
int main() {
    char a[100];
    char b[100];
    fgets(a, sizeof(a), stdin);
    fgets(b, sizeof(b), stdin);
    if ( !strncasecmp(a, b, sizeof(a)) ) {
        printf("Bingo!\n");
    } else {
        printf("Dead!\n");
    }
    return 0;
}

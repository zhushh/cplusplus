#include <stdio.h>
#include <string.h>

// void *memset(void *s, int c, size_t n);
int main() {
    char dest[100];
    memset(dest, 'H', sizeof(dest));
    dest[0] = 'a';
    dest[99] = '\0';
    printf("%s\n", dest);
    return 0;
}


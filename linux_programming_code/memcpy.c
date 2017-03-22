#include <stdio.h>
#include <string.h>

// void *memcpy(void *dest, void *src, sizt_t n);
int main() {
    char a[] = "hello world!";
    char b[100];
    memset(b, '\0', sizeof(b));
    memcpy(b, a, sizeof(b));
    printf("%s\n", b);
    return 0;
}


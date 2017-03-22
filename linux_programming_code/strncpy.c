#include <stdio.h>
#include <string.h>

// char *strncpy(char *dest, const char *src, size_t n);
int main() {
    char a[] = "astring(1)";
    char b[] = "bstring(2)";
    printf("before strncpy(), a = %s\n", a);
    printf("after strncpy(), a = %s\n", strncpy(a, b, sizeof(a)));
    return 0;
}


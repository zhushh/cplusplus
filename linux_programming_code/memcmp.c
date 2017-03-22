#include <stdio.h>
#include <string.h>

// int memcmp(const void *s1, const void *s2, size_t n);
int main() {
    char a[] = "aBcDeF";
    char b[] = "AbCdEf";
    printf("memcmp(a, b) = %d\n", memcmp(a, b, 6));
    return 0;
}


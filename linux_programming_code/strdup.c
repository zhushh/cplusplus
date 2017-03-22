#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char *strdup(const char *s);
// function allocate the same size memory to copy string s,
// then return the new memory address.
int main() {
    char a[] = "strdup";
    char *b;
    b = strdup(a);
    printf("b[] = %s\n", b);
    free(b);
    return 0;
}


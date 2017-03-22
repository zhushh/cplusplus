#include <stdio.h>

// int fscanf(FILE *stream, const char *format,...);
int main() {
    int i;
    unsigned int j;
    char s[5];
    // the next statement contains regular expression.
    fscanf(stdin, "%d %x %5[a-z] %s", &i, &j, s, s);
    printf("%d %d %s\n", i, j, s);
    return 0;
}


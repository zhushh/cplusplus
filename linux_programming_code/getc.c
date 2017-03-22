#include <stdio.h>

/* int getc(FILE* stream); */
int main() {
    int c;
    while ((c = getc(stdin)) != EOF)
        if (putc(c, stdout) == EOF)
            printf("output error");

    // int ferror(FILE *stream);
    // return nonzero if stream occured mistake.
    // zero will be return if success.
    if (ferror(stdin))
        printf("input error");

    return 0;
}


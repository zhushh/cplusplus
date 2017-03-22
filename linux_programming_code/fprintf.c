#include <stdio.h>

// int fprintf(FILE *stream, const char *format, ...);
int main() {
    int i = 100;
    int j = 12;
    double k = 3.5;
    fprintf(stdout, "%d %d %lf\n", i, j, k);
    /* character '*' will match the latter number 4 */
    fprintf(stdout, "%x %*d %lf\n", i, 4, j, k);
    return 0;
}


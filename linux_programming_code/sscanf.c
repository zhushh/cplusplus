#include <stdio.h>

// int sscanf(const char * str, const char * format, ...);
int main() {
    int i;
    unsigned int j;
    char input[] = "10 0x1b aaaaaaaa bbbbbbb";
    char s[5];
    sscanf(input, "%d %x %5[a-z] %s", &i, &j, s, s);
    printf("%d %d %s\n", i, j, s);
    return 0;
}


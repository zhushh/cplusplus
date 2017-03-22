#include <stdio.h>
#include <string.h>

// char *rindex(const char *s, int c);
int main() {
    char *str = "abcdefghijklmnopqrstuvwxyz";
    char ch = 'f';
    char *p = rindex(str, ch);
    printf("%s\n", p);
    return 0;
}


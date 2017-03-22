#include <stdio.h>

// int sprintf(char *str, const char *format, ...);
int main() {
    char * a = "This is a string A!";
    char buf[80];
    sprintf(buf, ">>>%s<<<\n", a);
    printf("%s\n", buf);
    return 0;
}


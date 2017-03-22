#include <stdio.h>
#include <string.h>

// char *strchr(const char *s, int c);
// if c does not exist in string s, then it will be core dumped.
int main() {
    char *s = "hello world!";
    char ch = 'w';
    char *p = strchr(s, ch);
    printf("%s\n", p);
    return 0;
}


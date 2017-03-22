#include <stdio.h>
#include <string.h>

// search the substring and return the address if found.
// char *strstr(const char *haystack, const char *needle);
int main() {
    char s[] = "Nice to meet you!";
    char *p;
    p = strstr(s, "meet");
    printf("%s\n", p);
    return 0;
}


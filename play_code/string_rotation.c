/*************************************************************************
	> File Name: string_rotation.c
	> Author: zhushh
	> Mail: 
	> Created Time: Sat 22 Nov 2014 11:40:29 AM CST
*************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX 1000

void str_rotation(char * src, int size) {
    int len = strlen(src);
    if (len > size) {
        char ch = *src;
        char *ptr = NULL, *cur = src;
        int count = 1;
        ptr = src + count * size % len;
        while (ptr != src) {
            *cur = *ptr;
            cur = ptr;
            count++;
            ptr = src + count * size % len;
        }
        *cur = ch;
    }
}

int main() {
    char str[MAX];
    int size;
    scanf("%s", str);
    scanf("%d", &size);
    str_rotation(str, size);
    printf("%s\n", str);
    return 0;
}


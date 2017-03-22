/***********************************************************************
 *  > File Name: sayHello.c
 *  > Author: zhushuhuang
 *  > Mail: zsh5318@gmail.com
 *  > Created Time: Wed 31 Dec 2014 07:13:11 PM CST
***********************************************************************/

#include <stdio.h>

int main() {
    char name[100];
    printf("input your name: ");
    scanf("%s", name);
    printf("%s, Hello!\n", name);
    return 0;
}


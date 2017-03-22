#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// int on_exit(void (*function)(int, void*), void * arg);
void my_exit(int status, void *arg) {
    printf("before exit() !\n");
    printf("exit(%d)\n", status);
    printf("arg = %s\n", (char *)arg);
}

int main() {
    char *str = "test";
    on_exit(my_exit, (void *)str);
    exit(1234);
    return 0;
}


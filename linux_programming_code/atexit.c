#include <stdio.h>
#include <stdlib.h>

// int atexit(void (*function)(void));
// 0 return if execute success
// else -1 will be returned.
// error will be write to errno
void my_function() {
    printf("before exit() !\n");
}

int main() {
    atexit(my_function);
    exit(0);
}


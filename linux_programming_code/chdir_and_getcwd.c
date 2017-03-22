#include <unistd.h>
#include <stdio.h>
#include "new_err.h"
#include "path_alloc.h"

/*
 * #include <unistd.h>
 *
 * int chdir(const char * pathname);
 * int fchdir(int filedes);
 * char *getcwd(char *buf, size_t size);
 */

int main(void) {
    char *ptr;
    int size;
    if (chdir("/home/zhuzhu/shuhuang/code") < 0)
        err_sys("chdir failed");

    ptr = path_alloc(&size);
    if (getcwd(ptr, size) == NULL)
        err_sys("getcwd failed");

    printf("cwd = %s\n", ptr);
    return 0;
}


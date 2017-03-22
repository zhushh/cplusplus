#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "new_err.h"

/*
 * #include <sys/types.h>
 * #include <sys/stat.h>
 * mode_t umask(mode_t cmask);
 *      mode_t include:
 *          S_IRUSR, S_IWUSR, S_IXUSR
 *          S_IRGRP, S_IWGRP, S_IXGRP
 *          S_IROTH, S_IWOTH, S_IXOTH
 */

int main(void) {
    umask(0);
    if (creat("foo", S_IRUSR | S_IWUSR |
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)
        err_sys("creat error for foo");

    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", S_IRUSR | S_IWUSR |
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)
        err_sys("creat error for bar");

    return 0;
}


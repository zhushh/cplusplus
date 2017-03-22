#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ourhdr.h"
#include "new_err.h"

/*
 * #include <sys/types.h>
 * #include <sys/stat.h>
 * #include <fcntl.h>
 * int creat(const char * pathname, mode_t mode);
 */
/*
 * #include <sys/types.h>
 * #include <unistd.h>
 * off_t lseek(int filedes, off_t offset, int whence);
 *      whence is one of SEEK_SET, SEEK_CUR and SEEK_END
 */

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void) {
    int fd;
    if ((fd = creat("file.test", FILE_MODE) < 0))
        err_sys("creat error");

    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    /* offset now = 10 */

    if (lseek(fd, 10, SEEK_SET) == -1)
        err_sys("lseek error");
    /* offset now = 40 */

    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");
    /* offset now = 50 */

    exit(0);
    return 0;
}


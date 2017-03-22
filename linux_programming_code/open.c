#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

/*
 * #include <sys/stat.h>
 * #include <sys/types.h>
 * #include <fcntl.h>
 * int open(const char * pathname, int flags);
 * int open(const char * pathname, int flags, mode_t mode);
 *      mode_t include:
 *          O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, 
 *          O_TRUNC, O_APPEND, O_NONBLOCK, O_SYNC...
 */
int main(void) {
    int fd;
    char s[] = "Linux Program!\n", buffer[80] = {0};
    fd = open("/home/zhuzhu/shuhuang/temp", O_WRONLY | O_CREAT);
    write(fd, s, sizeof(s));
    close(fd);
    fd = open("/home/zhuzhu/shuhuang/temp", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    close(fd);
    printf("%s\n", buffer);
    return 0;
}


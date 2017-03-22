#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// int isatty(int dest);
// char *ttyname(int dest);
int main(int argc,char **argv) {
    int fd;
    char * file = argv[1];
    fd = open(file, O_RDONLY);
    printf("%s", file);
    if (isatty(fd)) {
        printf(" is a tty.\n");
        printf("ttyname = %s.\n", ttyname(fd));
    } else {
        printf(" is not a tty.\n");
    }
    close(fd);
    return 0;
}


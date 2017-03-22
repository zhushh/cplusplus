#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* #include <string.h> */
/* char *strerror(int errnum); */

/* #include <stdio.h> */
/* void perror(const char * msg); */
int main(int argc, char *argv[]) {
    fprintf(stderr, "EACCESS: %s\n", strerror(EACCES));

    errno = ENOENT;
    perror(argv[0]);

    exit(0);
}


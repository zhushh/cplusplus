#include <unistd.h>     /* for getpid() function */
#include <stdio.h>
#include <stdlib.h>     /* for exit() function */

/* pid_t getpid(void); */
int main() {
    printf("Hello world from process ID %d\n", getpid());
    exit(0);
}


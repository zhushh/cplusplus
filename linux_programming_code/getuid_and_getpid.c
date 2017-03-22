#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/* uid_t getuid(void); */
/* gid_t getgid(void); */
int main() {
    printf("uid is %d\n", getuid());
    printf("gid is %d\n", getgid());
    return 0;
}


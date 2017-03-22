#include <stdio.h>
#include <unistd.h>

// int execl(const char * path, const *argv, ...);
// the last argv must be NULL
int main() {
    execl("/bin/ls", "ls", "-al", "/etc/passwd", NULL);
    return 0;
}


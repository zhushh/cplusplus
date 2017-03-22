#include <unistd.h>

// int execv(const char * path, char * const argv[]);
int main() {
    char * argv[] = {"ls", "-al", "/etc/passwd", (char*)0};
    execv("/bin/ls", argv);
    return 0;
}


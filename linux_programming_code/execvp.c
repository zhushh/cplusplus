#include <unistd.h>

// int execvp(const char * file, char * const argv[]);
int main() {
    char * argv[] = {"ls", "-al", "/etc/passwd", 0};
    execvp("ls", argv);
    return 0;
}


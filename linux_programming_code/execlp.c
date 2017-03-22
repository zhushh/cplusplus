#include <unistd.h>

// int execlp(const char * file, const char * argv, ...);
int main() {
    execlp("ls", "ls", "-al", "/etc/passwd", NULL);
    return 0;
}


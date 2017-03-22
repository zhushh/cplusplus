#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

/* pid_t wait(int *status); */
// wait()会暂时停止目前进程的执行，直到有信号来到或子进程结束。
// 如果在调用wait()时子进程已经结束，则wait()会立即返回子进程结束状态值。
// 子进程的结束状态值会由参数status返回,而子进程的进程识别码也会一快返回。
// 若不在意子进程的结束状态，则可把status设置为NULL。
int main() {
    pid_t pid;
    int status, i;
    if (fork() == 0) {
        printf("This is a child process. pid = %d\n", getpid());
        exit(5);
        return 0;
    } else {
        sleep(1);
        printf("This is a parent process, wait for child...\n");
        pid = wait(&status);
        i = WEXITSTATUS(status);
        printf("child's pid = %d, exit status = %d\n", pid, i);
    }
    return 0;
}


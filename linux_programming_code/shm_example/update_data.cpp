#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "Node.h"

int main() {
    key_t key = 1234;
    int shmids;
    Node* ptr;

    if ((shmids = shmget(key, SIZE*sizeof(Node), MODE|IPC_CREAT)) < 0) {
        printf("error of shmget\n");
        exit(1);
    }

    if ((ptr = (Node*)shmat(shmids, 0, 0)) == (void*)-1) {
        printf("error of shmat\n");
        exit(1);
    }

    for (int i = 0; i < SIZE; i++) {
        ptr[i].value = i;
        ptr[i].color = SIZE - i;
    }

    if (shmdt(ptr) == -1) {
        printf("error of shmdt\n");
        exit(1);
    }

    return 0;
}

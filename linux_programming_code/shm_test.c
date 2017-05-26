/*************************************************************************
 > File Name: shm_test.c
 > Author: zhushh
 > Mail: 
 > Created Time: Thu 25 May 2017 03:46:35 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ARRAY_SIZE  40000
#define MALLOC_SIZE 100000
#define SHM_SIZE    100000
#define SHM_MODE    0600

char array[ARRAY_SIZE];

int main(void) {
    int     shmid;
    char    *ptr, *shmptr;

    printf("array[] from %p to %p\n", (void*)&array[0], (void*)&array[ARRAY_SIZE]);
    printf("stack around %p\n", (void*)&shmid);

    if ((ptr = malloc(MALLOC_SIZE)) == NULL) {
        perror("malloc error");
    }
    printf("malloced from %p to %p\n", (void*)ptr, (void*)ptr+MALLOC_SIZE);

    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0) {
        perror("shmget error");
    }
    if ((shmptr = shmat(shmid, 0, 0)) == (void*)-1) {
        perror("shmat error");
    }
    printf("shared memory from %p to %p\n", (void*)shmptr, (void*)shmptr+SHM_SIZE);

    if (shmctl(shmid, IPC_RMID, 0) < 0) {
        perror("shmctl error");
    }

    exit(0);
}


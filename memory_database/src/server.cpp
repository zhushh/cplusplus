#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#define SHARE_KEY       1234
#define SHARE_SIZE      1024
#define SHARE_MODE      0666

#define DEFAULT_IP      "127.0.0.1"
#define DEFAULT_PORT    8889
#define BUFFER_SIZE     4096

int socket_bind(const char* ip, int port);
int do_accept(int listener);
void do_request(int fd);

int main(int argc, char** argv) {
    int shmid;
    // create share data
    shmid = shmget((key_t)SHARE_KEY, SHARE_SIZE * sizeof(int), SHARE_MODE|IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    int *data = (int*)shmat(shmid, 0, 0);
    if (data == (void*)-1) {
        perror("shmat");
        exit(1);
    }
    data[0] = 0;    // init array data size

    int listener;
    int clientFd;
    pid_t pid = 1;

    listener = socket_bind(DEFAULT_IP, DEFAULT_PORT);
    if (listener < 0) {
        exit(1);
    }

    while ((clientFd = do_accept(listener)) != -1) {
        if ((pid = fork()) < 0) {
            perror("fork");
            break;
        } else if (pid == 0) {  // child
            do_request(clientFd);
            break;
        } else {    // parent
            continue;
        }
    }

    if (pid > 0) {
        close(listener);
        if (shmctl(shmid, IPC_RMID, 0) < 0) {
            perror("shmctl");
            exit(1);
        }
    }
    return 0;
}

int socket_bind(const char* ip, int port) {
    int fd;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd < 0) {
        perror("socket");
        return -1;
    }

    if (bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind");
        return -1;
    }

    if (listen(fd, 20)) {
        perror("listen");
        return -1;
    }

    return fd;
}

int do_accept(int listener) {
    struct sockaddr_in remoteaddr;
    unsigned int addrlen = sizeof(remoteaddr);
    int newfd;

    newfd = accept(listener, (struct sockaddr*)&remoteaddr, &addrlen);

    if (newfd == -1) {
        perror("accept");
    }

    printf("server: new connection from %s on socket %d\n", inet_ntoa(remoteaddr.sin_addr), newfd);
    return newfd;
}

void do_request(int client) {
    int shmid;
    int *data;
    shmid = shmget((key_t)SHARE_KEY, 0, SHARE_MODE);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    if ((data = (int*)shmat(shmid, 0, 0)) == (void*)-1) {
        perror("shmat");
        exit(2);
    }

    char buffer[BUFFER_SIZE];
    char answer[BUFFER_SIZE];
    int nbytes = 0;

    while ((nbytes = recv(client, buffer, sizeof(buffer), 0)) > 0) {
        buffer[nbytes] = '\0';
        printf("client %d: %s\n", client, buffer);
        // sprintf(answer, "Server get: %s", buffer);
        if (buffer[0] == 'P') {
            sprintf(answer, "%s: to be continue", buffer);
        } else if (buffer[0] == 'A' || buffer[0] == 'G' || buffer[0] == 'D') {
            char opName;
            int opNum;
            sscanf(buffer, "%c[%d]", &opName, &opNum);

            int i;
            int n = data[0];
            switch(opName) {
                case 'A':
                    for (i = 1; i <= n; i++) {
                        if (data[i] >= opNum) break;
                    }
                    if (i > n || data[i] > opNum) {
                        data[0]++;      // array size increment
                        n++;
                        while (n > i) {
                            data[n] = data[n-1];
                            n--;
                        }
                        data[i] = opNum;
                        sprintf(answer, "%s: success", buffer);
                    } else {
                        sprintf(answer, "%d exits", opNum);
                    }
                    break;
                case 'G':
                    if (opNum <= 0) {
                        sprintf(answer, "%s: Underflow", buffer);
                    } else if (n >= opNum) {
                        sprintf(answer, "%d", data[opNum]);
                    } else {
                        sprintf(answer, "%s: Overflow", buffer);
                    }
                    break;
                case 'D':
                    for (i = 1; i <= n; i++) {
                        if (data[i] >= opNum) break;
                    }
                    if (i <= n && data[i] == opNum) {
                        data[0]--;
                        while (i < n) {
                            data[i] = data[i+1];
                            i++;
                        }
                        sprintf(answer, "%s: success", buffer);
                    } else {
                        sprintf(answer, "%d: does not exits", opNum);
                    }
            }
        } else {
            sprintf(answer, "Undefined: %s", buffer);
        }

        nbytes = send(client, answer, strlen(answer), 0);
    }

    if (nbytes < 0) {
        perror("recv");
    } else {
        printf("server: socket %d hung up\n", client);
    }

    shmdt(data);
}

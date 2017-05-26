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

int init_shared_data();
int socket_bind(const char* ip, int port);
int do_accept(int listener);
int do_request(int data[], const char* request, char* reponse);
void handle_client(int fd);

int main(int argc, char** argv) {
    int shmid;
    shmid = init_shared_data();
    if (shmid < 0) {
        exit(1);
    }

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
            close(listener);
            handle_client(clientFd);
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

int init_shared_data() {
    int shmid = shmget((key_t)SHARE_KEY, SHARE_SIZE * sizeof(int), SHARE_MODE|IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        return -1;
    }

    int *data = (int*)shmat(shmid, 0, 0);
    if (data == (void*)-1) {
        perror("shmat");
        return -1;
    }
    data[0] = 0;    // init array data size
    return shmid;
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

    printf("server start listening on %s:%d\n", ip, port);
    fflush(stdout);

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

int do_request(int data[], const char* request, char* response) {
    int i, n;
    n = data[0];

    if (request[0] == 'P') {
        sprintf(response, "%s: to be continue", request);
    } else if (request[0] != 'A' && request[0] != 'G' && request[0] != 'D') {
        sprintf(response, "%s: Undefined", request);
    } else {
        char opName;
        int opNum;
        sscanf(request, "%c[%d]", &opName, &opNum);
        switch(opName) {
                case 'A':
                    for (i = 1; i <= n; i++) {
                        if (data[i] >= opNum) break;
                    }
                    if (i > n || data[i] > opNum) {
                        data[0]++;      // array size increment
                        while (n >= i) {
                            data[n+1] = data[n];
                            n--;
                        }
                        data[i] = opNum;
                        sprintf(response, "%s: success", request);
                    } else {
                        sprintf(response, "%d exits", opNum);
                    }
                    break;
                case 'G':
                    if (opNum <= 0) {
                        sprintf(response, "%s: Underflow", request);
                    } else if (n >= opNum) {
                        sprintf(response, "%d", data[opNum]);
                    } else {
                        sprintf(response, "%s: Overflow", request);
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
                        sprintf(response, "%s: success", request);
                    } else {
                        sprintf(response, "%d: does not exits", opNum);
                    }
        }
    }

    return strlen(response);
}

void handle_client(int client) {
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
        nbytes = do_request(data, buffer, answer);
        nbytes = send(client, answer, strlen(answer), 0);
    }

    if (nbytes < 0) {
        perror("recv");
    } else {
        printf("server: socket %d hung up\n", client);
    }

    shmdt(data);
}

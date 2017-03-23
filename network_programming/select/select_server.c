/*************************************************************************
 > File Name: selectserver.c
 > Author: zhushh
 > Mail: 
 > Created Time: Thu 23 Mar 2017 04:58:51 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEFAULT_IP  "127.0.0.1"
#define PORT        8889
#define BUFLEN      4096

static char remoteIP[INET6_ADDRSTRLEN];
static char buf[BUFLEN];
static int nbytes;

static int fdmax;
static int listener;

static fd_set master;

int sendall(int s, char *buf, int *len);
int socket_bind(char* ip, int port);

int do_accept();
int do_read(int fd);
int do_write(int fd);

int main(void)
{
    listener = socket_bind(DEFAULT_IP, PORT);

    // Init and add listener to master set
    FD_ZERO(&master);
    FD_SET(listener, &master);

    // keep track of the biggest file decriptor
    fdmax = listener;

    for (;;) {
        fd_set read_fds = master;
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }

        // run through the existing connections looking for data ro read
        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == listener) {
                    // handler the new connections
                    do_accept();
                } else {
                    // handler data from a client
                    nbytes = do_read(i);
                    if (nbytes > 0) {
                        do_write(i);
                    }
                }
            }
        }
    }

    return 0;
}

int socket_bind(char* ip, int port)
{
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

    if (listen(fd, 10) < 0) {
        perror("listen");
        return -1;
    }

    return fd;
}

int do_accept()
{
    struct sockaddr_in remoteaddr;
    int addrlen = sizeof(remoteaddr);
    int newfd;

    newfd = accept(listener, (struct sockaddr*)&remoteaddr, &addrlen);

    if (newfd == -1) {
        perror("accept");
    }

    FD_SET(newfd, &master);
    fdmax = (newfd > fdmax? newfd : fdmax);

    printf("selectserver: new connection from %s on socket %d\n", 
        inet_ntoa(remoteaddr.sin_addr), newfd);

    return newfd;
}

int do_read(int fd)
{
    // int nbytes;
    nbytes = recv(fd, buf, sizeof(buf), 0);

    if (nbytes > 0) {
        return nbytes;
    } else if (nbytes < 0) {
        perror("revcv");
    } else if (nbytes == 0) {
        printf("selectserver: socket %d hung up\n", fd);
    }

    close(fd);
    FD_CLR(fd, &master);
    return nbytes;
}

int do_write(int fd)
{
    // int nbytes;
    int j;
    for (j = 0; j <= fdmax; j++) {
        if (FD_ISSET(j, &master)) {
            if (j != listener && j != fd) {
                if (sendall(j, buf, &nbytes) == -1) {
                    perror("sendall");
                    printf("We only send %d bytes because of the error\n", nbytes);
                    return nbytes;
                }
            }
        }
    }

    return nbytes;
}

int sendall(int s, char *buf, int *len)
{
    int total = 0;
    int byteself = *len;
    int n;

    while (total < *len) {
        n = send(s, buf+total, byteself, 0);
        if (n == -1) break;
        total += n;
        byteself -= n;
        // printf("send %d bytes\n", n);
    }

    *len = total;
    return n == -1?-1:0;
}

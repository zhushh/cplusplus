/*************************************************************************
 > File Name: selectclient.c
 > Author: zhushh
 > Mail: 
 > Created Time: Thu 23 Mar 2017 09:00:45 PM CST
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

#define STDIN 0

#define DEFAULT_IP "127.0.0.1"
#define PORT 8889
#define BUFLEN 2048

int sendall(int fd, char *buf, int *len) {
    int total = 0;
    int lenself = *len;
    int n;

    while (total < lenself) {
        n = send(fd, buf+total, sizeof(buf), 0);
        if (n < 0) { break; }
        total += n;
    }

    *len = total;
    return (n < 0 ? -1 : 0);
}

int main(int argc, char const *argv[])
{
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(DEFAULT_IP);

    int fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket");
        exit(1);
    }

    // int addrlen = sizeof(serv_addr);
    if (connect(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        exit(2);
    }

    int nbytes;
    char buf[BUFLEN];

    // the read_fds need initialization each time
    fd_set master;
    fd_set read_fds;
    FD_ZERO(&master);
    FD_SET(STDIN, &master);
    FD_SET(fd, &master);

    for (;;) {
        read_fds = master;

        if (select(fd+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(3);
        }

        if (FD_ISSET(STDIN, &read_fds)) {
            fgets(buf, sizeof(buf), stdin);
            nbytes = strlen(buf);
            if (sendall(fd, buf, &nbytes) == -1) {
                perror("sendall");
                fprintf(stderr, "Only send %d bytes because of error\n", nbytes);
                close(fd);
                break;
            }
        } else if (FD_ISSET(fd, &read_fds)) {
            if ((nbytes = recv(fd, buf, sizeof(buf), 0)) <= 0) {
                if (nbytes < 0) {
                    perror("recv");
                }

                close(fd);
                break;
            } else {
                printf("Recieve Mesg: %s", buf);
            }
        }
    }

    return 0;
}

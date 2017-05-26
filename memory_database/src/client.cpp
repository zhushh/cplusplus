#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEFAULT_IP      "127.0.0.1"
#define DEFAULT_PORT    8889
#define BUFFER_SIZE     4096

int main() {
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEFAULT_PORT);
    serv_addr.sin_addr.s_addr = inet_addr(DEFAULT_IP);

    int fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket");
        exit(1);
    }

    if (connect(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        exit(2);
    }

    char buff[BUFFER_SIZE];
    while (fgets(buff, BUFFER_SIZE, stdin)) {
        buff[strlen(buff) - 1] = '\0';
        if (strncmp(buff, "quit", 4) == 0) {
            break;
        }

        if (send(fd, buff, strlen(buff), 0) < 0) {
            perror("send");
            exit(3);
        }

        int nbytes = 0;
        if ((nbytes = recv(fd, buff, BUFFER_SIZE, 0)) < 0) {
            perror("recv");
            exit(4);
        } else if (nbytes == 0) {
            printf("server close.");
        } else {
            buff[nbytes] = '\0';
            printf("Response: %s\n", buff);
        }
    }

    close(fd);
    return 0;
}

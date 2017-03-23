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

#define PORT "8889"

// get sockaddr, IPv4 or IPv6
void* get_in_addr(struct sockaddr *sa) 
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
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

int main(void)
{
    fd_set master;
    fd_set read_fds;
    int fdmax;

    int listener;
    int newfd;
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen;

    char buf[2048];
    int nbytes;

    char remoteIP[INET6_ADDRSTRLEN];

    int yes = 1;
    int i, j,   rv;

    struct addrinfo hints, *ai, *p;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    // get us a socket and bind it
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = ai; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0) {
            continue;
        }

        // lose the presky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    // if we got here, it means we didn't get bound
    if (p == NULL) {
        fprintf(stderr, "selectserver: fail to bind\n");
        exit(2);
    }

    freeaddrinfo(ai);

    // listen 
    if (listen(listener, 10) == -1) {
        perror("listen");
        exit(3);
    }

    // add listener to master set
    FD_SET(listener, &master);

    // keep track of the biggest file decriptor
    fdmax = listener;

    for (;;) {
        read_fds = master;

        // printf("Start select\n");
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }

        // run through the existing connections looking for data ro read
        for (i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == listener) {
                    // handler the new connections
                    addrlen = sizeof(remoteaddr);
                    newfd = accept(listener, (struct sockaddr*)&remoteaddr, &addrlen);

                    if (newfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master);
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }

                        printf("selectserver: new connection from %s on socket %d\n", 
                            inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr*)&remoteaddr), remoteIP, INET6_ADDRSTRLEN), newfd);
                    }
                } else {
                    // handler data from a client
                    if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
                        // get error or connection closed by client
                        if (nbytes == 0) {
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
                            perror("recv");
                        }

                        close(i);
                        FD_CLR(i, &master);
                    } else {
                        // we get some data from a client
                        for (j = 0; j <= fdmax; j++) {
                            // send to everyone
                            if (FD_ISSET(j ,&master)) {
                                // except the listener and ourselves
                                if (j != listener && j != i) {
                                    //if (send(j, buf, nbytes, 0) == -1) {
                                    //    perror("send");
                                    //}
                                    if (sendall(j, buf, &nbytes) == -1) {
                                        perror("sendall");
                                        printf("We only send %d bytes because of the error\n", nbytes);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}


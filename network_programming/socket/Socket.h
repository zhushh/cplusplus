#ifndef __SOCKET__
#define __SOCKET__

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
using namespace std;

#define SOCKET_ERROR            (-1)
#define BUFSIZE                 4096
#define DEFAULT_IP              "127.0.0.1"

#define closesocket close 
#define IF_COND_PRINT_AND_EXIT(cond, str, status) \
if (cond) { printf("%s", str); exit(status); }

void Init_sockAddr_in(struct sockaddr_in& s, char* ip, int port);

class Socket {
public:
    bool sendSTR(string&);
    bool recvSTR(string&);
    virtual void InitSocket(char*, int) = 0;

    int getLocalSock() const;
    int getRemoteSock() const;
protected:
    int local_sock;
    int remote_sock;
};

class Server : public Socket {
public:
    Server(int);
    Server(char*, int);
    ~Server();
    bool isAccepted();
    std::string getRemoteAddr() const;
    virtual void InitSocket(char*, int);
private:
    struct sockaddr_in remote_addr;
};

class Client : public Socket {
public:
    Client();
    Client(char*, int);
    ~Client();
    virtual void InitSocket(char*, int);
};

#endif

#ifndef __SOCKET__
#define __SOCKET__


#ifdef WIN32

#include <WinSock2.h>
#include <stdio.h>
#include <Windows.h>

/* 要使用winsock API，就要包含ws2_32.lib这个库 */
#pragma comment(lib, "ws2_32.lib")

#else

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_SOCKET          (~0)
#define SOCKET_ERROR            (-1)

#define closesocket close 

#endif

#include <iostream>
#include <string>
using namespace std;


#define BUFSIZE     4096
#define DEFAULT_IP  "127.0.0.1"

#define IF_COND_PRINT(cond, str) if (cond) { printf("%s", str); }
#define IF_COND_EXIT(cond, status) if (cond) { exit(status); }
#define IF_COND_PRINT_AND_EXIT(cond, str, status) \
if (cond) { printf("%s", str); exit(status); }


void Init_sockAddr_in(struct sockaddr_in& s, char* ip, int port);

class Socket {
public:
    bool sendSTR(string&);
    bool recvSTR(string&);
    virtual void InitSocket(char*, int) = 0;
protected:
    unsigned int local_sock;
    unsigned int remote_sock;
};

class Server : public Socket {
public:
    Server(int);
    Server(char*, int);
    ~Server();
    bool isAccepted();
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

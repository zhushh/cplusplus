#include "Socket.h"

// init sockaddr_in 
void Init_sockAddr_in(struct sockaddr_in& sock_addr, char* ip, int port) {
    memset(&sock_addr, 0, sizeof(sockaddr_in));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = inet_addr(ip);
}

bool Socket::sendSTR(string& str) {
    int len = str.length();
    const char* ptr = str.c_str();

    while (len > 0) {
        int i = send(remote_sock, ptr, len, 0);
        if (i < 0) {
            return false;
        }
        ptr += i;
        len -= i;
    }

    return true; 
}

bool Socket::recvSTR(string& str) {
    int len = BUFSIZE;
    char buf[BUFSIZE + 1];
    int retVal = recv(local_sock, buf, len, 0);

    if (retVal <= 0) {
        return false;
    }

    buf[retVal] = '\0';
    str = string(buf);
    return true; 
}

int Socket::getLocalSock() const {
    return local_sock;
}

int Socket::getRemoteSock() const {
    return remote_sock;
}

Server::Server(int port) { InitSocket(DEFAULT_IP, port); }
Server::Server(char* ip, int port) { InitSocket(ip, port); }
Server::~Server() { closesocket(remote_sock); }

void Server::InitSocket(char* ip, int port) {
    printf("Start InitSocket\n");

    local_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    IF_COND_PRINT_AND_EXIT(local_sock < 0, "Create socket fail!\n", -1);

    // init sockaddr_in 
    struct sockaddr_in serv_addr;
    Init_sockAddr_in(serv_addr, ip, port);

    // binding
    int retVal = bind(local_sock, (sockaddr*)&serv_addr, sizeof(serv_addr));
    IF_COND_PRINT_AND_EXIT(retVal < 0, "Bind socket fail!\n", -1);

    printf("Binding succeed!\n");

    // listening
    IF_COND_PRINT_AND_EXIT(listen(local_sock, 10) < 0, "Listening fail!\n", -1);
    printf("Server %d is listening...\n", port);
}

bool Server::isAccepted() {
    memset(&remote_addr, 0, sizeof(sockaddr_in));
    unsigned int addrlen = sizeof(remote_addr);

    // accepting
    remote_sock = accept(local_sock, (sockaddr*)&remote_addr, &addrlen);
    // IF_COND_PRINT_AND_EXIT(remote_sock < 0, "Accept client fail!\n", -1);
    if (remote_sock < 0) { return false; }

    return true;
}

std::string Server::getRemoteAddr() const {
    return std::string(inet_ntoa(remote_addr.sin_addr));
}

Client::Client() {}
Client::Client(char* ip, int port) { InitSocket(ip, port); }
Client::~Client() { closesocket(remote_sock); }

void Client::InitSocket(char* ip, int port) {
    remote_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    IF_COND_PRINT_AND_EXIT(remote_sock < 0, "Create socket fail!\n", -1);

    // init sockaddr_in
    struct sockaddr_in serv_addr;
    Init_sockAddr_in(serv_addr, ip, port);

    // connecting
    int retVal = connect(remote_sock, (sockaddr*)&serv_addr, sizeof(serv_addr));
    IF_COND_PRINT_AND_EXIT(retVal < 0, "Connect to server fail!\n", -1);
    printf("Connect to server %s:%d succeed!\n", ip, port);
}

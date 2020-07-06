#include <stdio.h> //printf(), fprintf(), perror()
#include <sys/socket.h> //socket(), bind(), accept(), listen()
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa(), inet_aton()
#include <stdlib.h> //atoi(), exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <string.h> //memset(), strcmp()
#include <unistd.h> //close()
#include <iostream>

#define QUEUELIMIT 5
#define BUFSIZE    5

typedef const char     c_char;
typedef unsigned short u_short;

class MemoServer
{
private:
    const u_short       _port;
    u_short             _servPort;       // server port number

    int                 _servSock;       // server socket descriptor
    int                 _clitSock;       // client socket descriptor
    struct sockaddr_in  _servSockAddr;   // server internet socket address
    struct sockaddr_in  _clitSockAddr;   // client internet socket address
    
    unsigned int        _clitLen;        // client internet socket address length
    char*               _recvBuffer;     // receive temporary buffer
    char*               _sendBuffer;     // send temporary buffer
    int                 _recvMsgSize;    // recieve buffer size
    int                 _sendMsgSize;    // send buffer size
    
public:
    MemoServer(const u_short port);
    ~MemoServer(void);

    void  Send(c_char* text);
    char* Recv(void);
};
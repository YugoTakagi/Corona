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

class TcpClient
{
private:
    const u_short       _port;
    c_char*             _ip_addres;


    int                 _sock;           // local socket descriptor
    struct sockaddr_in  _servSockAddr;   // server internet socket address
    u_short             _servPort;       // server port number
    char*               _recvBuffer;     // receive temporary buffer
    char*               _sendBuffer;     // send temporary buffer
    int                 _recvMsgSize;    // recieve buffer size
    int                 _sendMsgSize;    // send buffer size

    void WriteSockaddr_in(c_char* ip_addres);
    void WritePort(const u_short port);
    void MakeSocket(void);
    void Connect(void);
public:
    TcpClient(const u_short port, c_char* ip_addres);
    ~TcpClient(void);

    void  Send(c_char* text);
    char* Recv(void);
};
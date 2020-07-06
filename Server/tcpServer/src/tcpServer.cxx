#include "../inc/tcpServer.hpp"

MemoServer::MemoServer(const u_short port)
: _port(port)
{
    // OSへの手続き書類( sockaddr_in )の作成 : ローカルホストのアドレス
    if ((_servPort = _port) == 0)
    {
        std::cerr << "Invalid port number." << std::endl;
        exit(EXIT_FAILURE);
    }

    if ((_servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
    {
        std::cerr << "socket() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    memset(&_servSockAddr, 0, sizeof(_servSockAddr));
    _servSockAddr.sin_family      = AF_INET;
    _servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    _servSockAddr.sin_port        = htons(_servPort);

    // ソケットとポート番号, アドレスを結びつける
    if (bind(_servSock, (struct sockaddr *) &_servSockAddr, sizeof(_servSockAddr) ) < 0 )
    {
        std::cerr << "bind() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    // ソケットを接続待ち状態にする
    if (listen(_servSock, QUEUELIMIT) < 0)
    {
        std::cerr << "listen() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    /* ----- */
    _clitLen = sizeof(_clitSockAddr);

    // acceptはプログラムを停止してしまう.
    if ((_clitSock = accept(_servSock, (struct sockaddr *) &_clitSockAddr, &_clitLen)) < 0)
    {
        std::cerr << "accept() failed." <<std::endl;
        exit(EXIT_FAILURE);
    }
    printf("connected from %s.\n", inet_ntoa(_clitSockAddr.sin_addr));

    _recvBuffer = new char[BUFSIZE];
    _sendBuffer = new char[BUFSIZE];
}

MemoServer::~MemoServer()
{
    close(_clitSock);
    close(_servSock);

    delete[] _recvBuffer;
    delete[] _sendBuffer;
}

void MemoServer::Send(c_char* text)
{
    strcpy(_sendBuffer, text);
    if (send(_clitSock, _sendBuffer, strlen(_sendBuffer), 0) <= 0)
    {
        std::cerr << "send() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
}

char* MemoServer::Recv(void)
{
    if ((_recvMsgSize = recv(_clitSock, _recvBuffer, BUFSIZE, 0)) < 0)
    {
        perror("recv() failed.");
        exit(EXIT_FAILURE);
    } 
    else if(_recvMsgSize == 0)
    {
        fprintf(stderr, "connection closed by foreign host.\n");
    }
    return _recvBuffer;
}


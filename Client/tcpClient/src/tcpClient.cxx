#include "../inc/tcpClient.hpp"

TcpClient::TcpClient(const u_short port, c_char* ip_addres)
: _port(port)
, _ip_addres(ip_addres)
{
    WriteSockaddr_in(_ip_addres);
    WritePort(_port);
    MakeSocket();
    Connect();
    _recvBuffer = new char[BUFSIZE];
    _sendBuffer = new char[BUFSIZE];
}

TcpClient::~TcpClient(void)
{
    close(_sock);
    // std::cout << "close _sock." << std::endl;

    delete[] _recvBuffer;
    delete[] _sendBuffer;
}

void TcpClient::WriteSockaddr_in(c_char* ip_addres)
{// OSへの手続き書類( sockaddr_in )の作成 : 接続先ホストのアドレス

    memset(&_servSockAddr, 0, sizeof(_servSockAddr));
    _servSockAddr.sin_family = AF_INET;
    if (inet_aton(ip_addres, &_servSockAddr.sin_addr) == 0) 
    {
        std::cerr << "Invalid IP Address." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void TcpClient::WritePort(const u_short port)
{// port番号を指定
    if ((_servPort = port) == 0)
    {
        std::cerr << "invalid port number." << std::endl;
        exit(EXIT_FAILURE);
    }
    _servSockAddr.sin_port = htons(_servPort);
}

void TcpClient::MakeSocket(void)
{// ソケットの作成
    if ((_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
    {
        std::cerr << "socket() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void TcpClient::Connect(void)
{// 2つのソケットをコネクト
    if (connect(_sock, (struct sockaddr*) &_servSockAddr, sizeof(_servSockAddr)) < 0) 
    {
        std::cerr << "connect() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "connect to " << inet_ntoa(_servSockAddr.sin_addr) << std::endl;
}

void TcpClient::Send(c_char* text)
{
    strcpy(_sendBuffer, text);
    if (send(_sock, _sendBuffer, strlen(_sendBuffer), 0) <= 0)
    {
        std::cerr << "send() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
}

char* TcpClient::Recv(void)
{
    if ((_recvMsgSize = recv(_sock, _recvBuffer, sizeof(_recvBuffer), 0)) < 0)
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
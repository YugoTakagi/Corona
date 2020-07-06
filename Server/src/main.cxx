#include <tcpServer.hpp>

#define START "start"
#define END   "end.."
#define READY "ready"

bool CheckRecv(TcpServer& serv, const char* flag);
int main(void)
{
    std::cout << "[Server] Hi! Let's start!" << std::endl;
    unsigned short port[] = {8100};
    // unsigned short port[] = {8100, 8200};
    // int size = sizeof(port) / sizeof(unsigned short);

    TcpServer serv1(port[0]);
    // TcpServer serv2;

    CheckRecv(serv1, READY);
    // Check(serv2, READY);

    serv1.Send(START);
    // serv2.Send(START);

    if(CheckRecv(serv1, END)) serv1.Send(END);
    // if(Check(serv2, END)) serv2.Send(END);

    std::cout << "[Server] That's it." << std::endl;
    
    return 0;
}

bool CheckRecv(TcpServer& serv, const char* flag)
{
    while(true)
    {// Recv ReadFlag from Client.
        
        char* recvBuffer = serv.Recv();
        // std::cout << "[Server] Recv ["<< recvBuffer <<"] from Client."<< std::endl;
        if(!strcmp(recvBuffer, flag))
        {
            std::cout << "[Client] I'm "<< recvBuffer << "." << std::endl;
            return true;
            break;
        }
    }
    return false;
}

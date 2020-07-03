#include "../inc/log.hpp"
#include "../inc/tcpClient.hpp"
#include "../inc/muscle.hpp"

#include "../inc/define.hpp"

float StateForce();
bool Check(MemoClient& clie, const char* flag);

int main(int argc, char const *argv[])
{
/* ============================================================== */
// Init
    const float ref1[]= 
    {
        #include IFILE1
    };
    const int size = sizeof(ref1) / sizeof(float);

    Muscle vasInt(DT, PGAIN, IGAIN, DGAIN);
    Log LogOfvasInt(size);
    LogOfvasInt.RecordPidGain(PGAIN, IGAIN, DGAIN);
// ~Inti 
/* ============================================================== */
// Get permission from Server
    unsigned short port = atoi(argv[1]); // 8100
    const char* addr = "127.0.0.1"; // localhost: 127.0.0.1
    MemoClient client(port, addr);

    bool startFlag = false;

    std::cout << "[Client] I'm ready!" << std::endl;
    client.Send(READY);
    if(Check(client, START)) startFlag = true;
// ~Get permission from Server
/* ============================================================== */
// Start muscle control
    float reff = 0.0;
    float mesf = 0.0;
    int index = 0;
    while(startFlag)
    {
        if(index == size) break;
    // main loop

        reff = ref1[index];
        mesf = StateForce();

        std::cout <<"["<< index <<"] ";
        LogOfvasInt.Record(index, reff, mesf, vasInt.Stretch(reff, mesf));

    // ~main loop
        ++index;
    }
    client.Send(END);
    Check(client, END);
// ~Start muscle control
/* ============================================================== */
// Make log
    LogOfvasInt.Save(OFILE1);
// ~Make log
/* ============================================================== */
    std::cout << "[Client] That's it." << std::endl;
    return 0;
}

float StateForce()
{
    float stForce = 0.0;
    // run code


    // ~run code
    return stForce;
}

bool Check(MemoClient& clie, const char* flag)
{
    while(true)
    {
        char* recvBuffer = clie.Read();
        if(!strcmp(recvBuffer, flag))
        {
            std::cout << "[Server] I'm "<< recvBuffer << "." << std::endl;
            return true;
            break;
        }
    }
    return false;
}
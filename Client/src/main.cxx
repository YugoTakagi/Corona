#include "../inc/log.hpp"
#include "../inc/tcpClient.hpp"
#include "../inc/muscle.hpp"

#include "../inc/define.hpp"

typedef const float c_float;

bool Check(MemoClient& clie, const char* flag);


int main(int argc, char const *argv[])
{
/* ============================================================== */
// Init
    c_float ref_table[] = {
        #include IFILE1
    };
    const int size = sizeof(ref_table) / sizeof(const float);

    Muscle vasInt(DT, PGAIN, IGAIN, DGAIN);
    Log LogOfvasInt(size);
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
    float reff  = 0.0;
    float mesf  = 0.0;
    int   index = 0;
    while(startFlag)
    {
        if(index == size) break;
    // main loop


        reff = ref_table[index];

        std::cout <<"["<< index <<"] ";
        LogOfvasInt.Record
        (
            index,
            vasInt.Stretch(reff)
        );


    // ~main loop
        ++index;
    }
    client.Send(END);
    Check(client, END);
// ~Start muscle control
/* ============================================================== */
// Save log
    float gainBuffer[3] = {};
    vasInt.GetGain(gainBuffer);
    LogOfvasInt.RecordPidGain(gainBuffer);
    LogOfvasInt.Save(OFILE1);
// ~Save log
/* ============================================================== */
    std::cout << "[Client] That's it." << std::endl;
    return 0;
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
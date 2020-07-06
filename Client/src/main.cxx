#include <muscle.hpp>
#include <tcpClient.hpp>
#include "../inc/log.hpp"
#include "../inc/define.hpp"

typedef const float c_float;

bool CheckRecv(MemoClient& clie, const char* flag);

int main(int argc, char const *argv[])
{
/* ============================================================== */
// Init
    c_float ref_table[] = {
        #include INPUT_FILE_A
    };
    const int size = sizeof(ref_table) / sizeof(const float);

    unsigned short port = atoi(argv[1]); // 8100
    const char* addr = "127.0.0.1"; // localhost: 127.0.0.1
    MemoClient client(port, addr);

    Muscle vasInt(DT, PGAIN, IGAIN, DGAIN);
    Log LogOfvasInt(size);
// ~Inti
/* ============================================================== */
// Get permission from Server
    bool startFlag = false;
    std::cout << "[Client] I'm ready!" << std::endl;
    client.Send(READY);
    if(CheckRecv(client, START)) startFlag = true;
// ~Get permission from Server
/* ============================================================== */
// Start muscle control
    int index = 0;
    while(startFlag)
    {
        if(index == size) break;
    // main loop


        std::cout <<"["<< index <<"] ";
        LogOfvasInt.Record
        (
            index,
            vasInt.Stretch(ref_table[index])
        );


    // ~main loop
        ++index;
    }
    client.Send(END);
    CheckRecv(client, END);
// ~Start muscle control
/* ============================================================== */
// Save log
    float gainBuffer[3] = {};
    vasInt.GetGain(gainBuffer, sizeof(gainBuffer));
    LogOfvasInt.RecordPidGain(gainBuffer, sizeof(gainBuffer));
    LogOfvasInt.Save(OUTPUT_FILE_A);
// ~Save log
/* ============================================================== */
    std::cout << "[Client] That's it. See you." << std::endl;
    return 0;
}

bool CheckRecv(MemoClient& clie, const char* flag)
{
    while(true)
    {
        char* recvBuffer = clie.Recv();
        if(!strcmp(recvBuffer, flag))
        {
            std::cout << "[Server] I'm "<< recvBuffer << "." << std::endl;
            return true;
            break;
        }
    }
    return false;
}
#include <muscle.hpp>
#include <tcpClient.hpp>
#include "../inc/log.hpp"
#include "../inc/define.hpp"

typedef const float c_float;

bool CheckRecv(TcpClient& clie, const char* flag);
void SetOption(const int argc, char* const *data);

int main(int argc, char* const *argv)
{
    SetOption(argc, argv);
/* ============================================================== */
// Init
    c_float ref_table[] = {
        #include INPUT_FILE_A
    };
    const int size = sizeof(ref_table) / sizeof(const float);

    // unsigned short port = atoi(argv[1]); // 8100
    // const char* addr = argv[2]; // localhost: 127.0.0.1
    // TcpClient client(port, addr);

    Muscle vasInt(0x04, 13, DT, PGAIN, IGAIN, DGAIN);
    Log LogOfvasInt(size);
// ~Inti
/* ============================================================== */
// Get permission from Server
    // bool startFlag = false;
    // std::cout << "[Client] I'm ready!" << std::endl;
    // client.Send(READY);
    // if(CheckRecv(client, START)) startFlag = true;
// ~Get permission from Server
/* ============================================================== */
// Start muscle control
    int index = 0;
    // while(startFlag)
    while(true)
    {
        if(index == size) break;
    // main loop


        std::cout <<"["<< index <<"] ";
        LogOfvasInt.Record
        (
            index,
            vasInt.Stretch(ref_table[index])
        );
        usleep(20000); // 20ms

    // ~main loop
        ++index;
    }
    // client.Send(END);
    // CheckRecv(client, END);
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

bool CheckRecv(TcpClient& clie, const char* flag)
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


void SetOption(const int argc, char* const *data)
{

	int opt = 0; //getopt()のエラーメッセージを無効にする。
	while ((opt = getopt(argc, data, "hi:o:f:e:")) != -1)
    {
		switch (opt) {
			case 'h': // ヘルプ
				std::cout << "ex: ./main 8100 127.0.0.1" << std::endl;
				exit(0);

			// case 'i':	// 入力
			// 	this->i_filename = std::string(optarg);
			// 	break;

			// case 'o':	// 出力
			// 	this->o_filename = std::string(optarg);
			// 	break;

			// case 'f':	// 初期フレーム
			// 	this->first_frame = atoi(optarg);
			// 	break;

			// case 'e':	// 最終フレーム
			// 	this->end_frame = atoi(optarg);
			// 	break;

			default: //指定していないオプションが渡された場合
				std::cout << "指定していないオプション" << std::endl;
				// std::cout << "Usage: $ ./main [-h] [-i] arg1 [-o] arg2 [-f] arg3 [-e] arg4 ..." << std::endl;
				exit(0);
		}
	}
}

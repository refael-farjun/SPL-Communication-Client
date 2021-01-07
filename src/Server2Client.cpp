//
// Created by spl211 on 06/01/2021.
// encode

#include "Server2Client.h"
//ConnectionHandler handler = new ConnectionHandler("127.0.0.1", 7777);
Server2Client::Server2Client(int id, ConnectionHandler &handler, std::mutex &mutex) : _handler(handler) ,
                        _mutex(mutex), shouldTerminate(false) {

}

void Server2Client::stop() {
    shouldTerminate = true;
    myThread->join();
    delete myThread;
    myThread = nullptr;
}


void Server2Client::start(){
    myThread = new std::thread(&Server2Client::run, this);
    myThread->join();
}

void Server2Client::run() {
    while (!shouldTerminate){
        char byteOpcode[2];
        if (!_handler.getBytes(byteOpcode, sizeof(byteOpcode))) {
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        break;
        }
//        short opcode = bytesToShort(byteOpcode);
//        if (opcode == 12){
//            processErrMsg();
//        }
//        if (opcode == 13){
//            processErrMsg();
//        }



    }
}


short bytesToShort(char* bytesArr){
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

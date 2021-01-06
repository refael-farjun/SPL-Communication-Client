//
// Created by spl211 on 06/01/2021.
// encode

#include "Server2Client.h"
//ConnectionHandler handler = new ConnectionHandler("127.0.0.1", 7777);
Server2Client::Server2Client(int id, ConnectionHandler &handler, std::mutex &mutex) : _id(id), _handler() _mutex(mutex) {
//    this->_handler = handler;

}

void Server2Client::run() {

}

short bytesToShort(char* bytesArr){
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}
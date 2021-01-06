//
// Created by spl211 on 06/01/2021.
//

#ifndef BOOST_ECHO_CLIENT_SERVER2CLIENT_H
#define BOOST_ECHO_CLIENT_SERVER2CLIENT_H
#include <iostream>
#include <mutex>
#include <thread>
#include "connectionHandler.h"

class Server2Client{
private:
    ConnectionHandler _handler;
    std::mutex & _mutex;
    int _id;
public:
    Server2Client(ConnectionHandler& handler, std::mutex& mutex);

    void run();

    short bytesToShort(char* bytesArr);

    void processAckMsg();

    void processErrMsg();



};
#endif //BOOST_ECHO_CLIENT_SERVER2CLIENT_H

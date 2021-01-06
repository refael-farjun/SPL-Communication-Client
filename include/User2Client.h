//
// Created by spl211 on 06/01/2021.
//

#ifndef BOOST_ECHO_CLIENT_USER2CLIENT_H
#define BOOST_ECHO_CLIENT_USER2CLIENT_H
#include <iostream>
#include <mutex>
#include <thread>
#include "connectionHandler.h"
#include <vector>
#include <string>
class User2client{
private:
    ConnectionHandler & _handler;
    std::mutex & _mutex;
    std::thread *myThread;
    bool shouldTerminate;

public:
    User2client(ConnectionHandler &handler, std::mutex& mutex);
    void run();

    std::vector<std::string> split(std::string, std::string delimiter);

    void encode(std::vector<std::string>);


    void start()
    {
        myThread = new std::thread(&User2client::run, this);
    }

    void stop()
    {
        shouldTerminate = true;
        myThread->join();
        delete myThread;
        myThread = nullptr;
    }

};
#endif //BOOST_ECHO_CLIENT_USER2CLIENT_H

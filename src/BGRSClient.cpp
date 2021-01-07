//
// Created by spl211 on 06/01/2021.
//
#include "BGRSClient.h"
#include "User2Client.h"
#include "Server2Client.h"

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

//    std::thread t;
    std::mutex mutex;
    User2client user2client(connectionHandler, mutex);
    Server2Client server2Client(connectionHandler, mutex);
//    t = new std::thread(&User2client::start, &user2client);
    std::thread t1(&User2client::run, &user2client);
    std::thread t2(&Server2Client::run, &server2Client);
    t1.join();
    t2.join();
//    user2client.start();
//    server2Client.start();
//    Server2Client server2Client(_handler, _mutex);
//    server2Client.start();



    return 0;


}
//
// Created by spl211 on 06/01/2021.
//
#include "BGRSClient.h"
#include "User2Client.h"

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

    std::thread t;
    std::mutex mutex;
    User2client user2client(connectionHandler, mutex);
    user2client.start();



    return 0;


}
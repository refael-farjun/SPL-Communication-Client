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

//    std::thread t1(&User2client::run, &user2client);
//    std::thread t2(&Server2Client::run, &server2Client);

    std::thread *myThread1;
    myThread1 = new std::thread(&User2client::run, &user2client);

    std::thread *myThread2;
    myThread2 = new std::thread(&Server2Client::run, &server2Client);

    myThread1->join();
    myThread2->join();

    delete myThread1;
    delete myThread2;

//    t2.join();

    exit(0);

//    t1.join();



//    void Server2Client::stop() {
//        shouldTerminate = true;
////    myThread->join();
//        delete myThread;
//        myThread = nullptr;
//    }
//
//
//    void Server2Client::start(){
//        myThread = new std::thread(&Server2Client::run, this);
////    myThread->join();
//    }


}
//
// Created by spl211 on 06/01/2021.
// decode
#include "User2Client.h"


User2client::User2client(ConnectionHandler &handler, std::mutex &mutex) : _handler(handler), _mutex(mutex) {

}

void User2client::run() {
    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len = line.length();
        std::cout << "line: " << line << std::endl;
//        if (!_handler.sendLine(line)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.

        std::vector<std::string> strVec = split(line);
        std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;

    }
}

std::vector<std::string> User2client::split(std::string) {

}
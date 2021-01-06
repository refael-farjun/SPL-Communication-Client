//
// Created by spl211 on 06/01/2021.
// decode
#include "User2Client.h"


User2client::User2client(ConnectionHandler &handler, std::mutex &mutex) : _handler(handler), _mutex(mutex),
                        shouldTerminate(false) {
}

void shortToBytes(short num, char* bytesArr)
{
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

void User2client::run() {
    std::cout << "in run" << std::endl;

    while (!shouldTerminate) {

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

        std::vector<std::string> strVec = split(line, " ");
        encode(strVec);
        std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;

    }
}

std::vector<std::string> User2client::split(std::string line, std::string delimiter) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> strVec;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        strVec.push_back(token);
//        std::cout << token << std::endl;
        line.erase(0, pos + delimiter.length());
    }
    return strVec;
//    std::cout << line << std::endl;

}

void User2client::encode(std::vector<std::string> strVec) {

    std::cout << strVec.size() << std::endl;
    int bufferSize = 2;
    for (size_t i = 1; i < strVec.size(); i++)
    {
        bufferSize += strVec[i].size();
        std::cout << strVec[i] << std::endl;
    }

    if (strVec[0] == "ADMINREG"){
        // encode by op


    }
    else if (strVec[0] == "STUDENTREG"){
        // encode by op
        bufferSize += 2;
        char *toSend = new char[bufferSize];
        shortToBytes(3, toSend);

        for (size_t i = 1; i < strVec.size(); i++)
            strcpy(toSend + 1 + (i - 1) * strVec[i].size(), strVec[i].c_str());

        std::cout << bufferSize<< std::endl;

        _handler.sendBytes(toSend, bufferSize);

        delete[] toSend;
    }
    else if (strVec[0] == "LOGIN"){
        // encode by op
    }
    else if (strVec[0] == "LOGOUT"){
        // encode by op
    }
    else if (strVec[0] == "COURSEREG"){
        // encode by op
    }
    else if (strVec[0] == "KDAMCHECK"){
        // encode by op
    }
    else if (strVec[0] == "COURSESTAT"){
        // encode by op
    }
    else if (strVec[0] == "STUDENTSTAT"){
        // encode by op
    }
    else if (strVec[0] == "ISREGISTERED"){
        // encode by op
    }
    else if (strVec[0] == "UNREGISTER"){
        // encode by op
    }
    else if (strVec[0] == "MYCOURSES"){
        // encode by op
    }


}



//
// Created by spl211 on 06/01/2021.
// encode

#include "Server2Client.h"
//ConnectionHandler handler = new ConnectionHandler("127.0.0.1", 7777);
Server2Client::Server2Client(ConnectionHandler &handler, std::mutex &mutex) : _handler(handler) ,
                        _mutex(mutex), shouldTerminate(false) {

}

void Server2Client::stop() {
    shouldTerminate = true;
    myThread->join();
    delete myThread;
    myThread = nullptr;
}


void Server2Client::start(){
    for (size_t i = 0; i < 20; i++)
    {
        std::cout << "server !!!"  << std::endl;
    }
    myThread = new std::thread(&Server2Client::run, this);
    myThread->join();
}

void Server2Client::kdamCheck() { //print the list of the KDAM courses
    std::string kdamCourses;
    if (!_handler.getLine(kdamCourses)){
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }
    std::cout << kdamCourses << std::endl;
}

void Server2Client::c() { //print the list of the KDAM courses
    std::string kdamCourses;
    if (!_handler.getLine(kdamCourses)){
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }
    std::cout << kdamCourses << std::endl;
}

void Server2Client::optional(short messageOp) {
    if(messageOp == 4){ // message opcode was - "LOGOUT"
        // SHOULD TERMINATE !!!!!!
    }
    if(messageOp == 6){ // message opcode was - "KDAMCHECK"
        kdamCheck(); //print the KDAM courses
    }
    if(messageOp == 7){ // message opcode was - "COURSESTAT"
        courseStat(); // prints the state of the course
    }
    if(messageOp == 9){ // message opcode was - "STUDENTSTAT"
        studentStat(); // prints the state of the student
    }
    if(messageOp == 11){ // message opcode was - "MYCOURSES"
        myCourses(); // prints the list of the courses numbers that the student has registered to
    }
    else{ //messageOp that doesn't have 'optional'
        char emptyOptional[1];
        if (!_handler.getBytes(emptyOptional, sizeof(emptyOptional))){
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            return;
        }
        return;
    }


}

void Server2Client::processAckMsg() {
    char msgOp[2];
    if (!_handler.getBytes(msgOp, sizeof(msgOp))) {
        std::cout << "Disconnected. Exiting..... \n" << std::endl;
        return;
    }
    short messageOpcode = bytesToShort(msgOp); //opcode to know if its ack(12) or error(13)
    std::cout << "ACK " << messageOpcode << std::endl;
    optional(messageOpcode);
}

void Server2Client::processErrMsg() {
    char msgOp[2];
    if (!_handler.getBytes(msgOp, sizeof(msgOp))) {
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }
    short messageOpcode = bytesToShort(msgOp);
    std::cout << "ERROR " << messageOpcode << std::endl;
    }


void Server2Client::run() {
    while (!shouldTerminate){
        char byteOpcode[2];
        if (!_handler.getBytes(byteOpcode, sizeof(byteOpcode))) {
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        break;
        }
        short opcode = bytesToShort(byteOpcode);
        std::cout << opcode << std::endl;
        if (opcode == 12){ //ack message received
            processAckMsg();
        }
        if (opcode == 13){ //error message received
            std:: cout << "13" << std::endl;
            processErrMsg();
        }
        memset(byteOpcode, 0, sizeof(byteOpcode));



    }
}




short Server2Client::bytesToShort(char* bytesArr){
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

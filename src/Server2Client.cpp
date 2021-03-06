//
// Created by spl211 on 06/01/2021.
// encode

#include "Server2Client.h"
//ConnectionHandler handler = new ConnectionHandler("127.0.0.1", 7777);
Server2Client::Server2Client(ConnectionHandler &handler, std::mutex &mutex) : _handler(handler) ,
                                                                              _mutex(mutex), shouldTerminate(false) {

}

void Server2Client::kdamCheck() { //print the list of the KDAM courses
    std::string kdamCourses;
    if (!_handler.getLine(kdamCourses)){
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }
    std::cout << kdamCourses << std::endl;
}

void Server2Client::courseStat() { //print the list of the KDAM courses
    std::string course;
    if (!_handler.getLine(course)){
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }
    std::cout << course << std::endl; //Course: (<courseNum>) <courseName>
    std::string seatAvailable;
//    if() should implamnt if condition....................................................
}

void Server2Client::studentStat() { //print the list of the KDAM courses
    std::string studentStat;
    if (!_handler.getLine(studentStat)){
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }
    std::cout << studentStat << std::endl;
}

void Server2Client::myCourses() { //print the list of the KDAM courses
    std::string myCourses;
    if (!_handler.getLine(myCourses)){
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }
    std::cout << myCourses << std::endl;
}

void Server2Client::optional(short messageOp) {
    if(messageOp == 4){ // message opcode was - "LOGOUT"
        // SHOULD TERMINATE !!!!!!
        std::lock_guard<std::mutex> lock(_mutex);
        _handler.setTerminate(true);

    }
    else if(messageOp == 6){ // message opcode was - "KDAMCHECK"
        kdamCheck(); //print the KDAM courses
    }
    else if(messageOp == 7){ // message opcode was - "COURSESTAT"
        courseStat(); // prints the state of the course
    }
    else if(messageOp == 8){ // message opcode was - "STUDENTSTAT"
        studentStat(); // prints the state of the student
    }
    else if(messageOp == 9){ // message opcode was - "Isregistered"
        isRegistered(); // print if the student is registered or not
    }

    else if(messageOp == 11){ // message opcode was - "MYCOURSES"
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

void Server2Client::isRegistered(){
    std::string isRegisterd;
    if (!_handler.getLine(isRegisterd)){
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }
    std::cout << isRegisterd << std::endl;
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
    while (!_handler.getTerminate()){
        char byteOpcode[2];
        if (!_handler.getBytes(byteOpcode, sizeof(byteOpcode))) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        short opcode = bytesToShort(byteOpcode);
//        std::cout << opcode << std::endl;
        if (opcode == 12){ //ack message received
            processAckMsg();
        }
        if (opcode == 13){ //error message received
//            std:: cout << "13" << std::endl;
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

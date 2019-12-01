#include <iostream>
#include <string>
#include "../include/Session.h"


void Exit::act(Session& sess){
    complete();
    sess.addActionLog(this);
}
std::string Exit::toString() const{
    std::string output;
    if (getStatus() == ERROR){
        output = "Exit ERROR" + getErrorMsg();
    }

    if (getStatus() == COMPLETED){
        output = "Exit COMPLETED";
    }
    if (getStatus() == PENDING){
        output = "Exit PENDING";
    }
    return output;
}

BaseAction* Exit::clone(){
    return (new Exit(*this));
}

Exit::~Exit() {}
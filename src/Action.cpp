//
// Created by maiy@wincs.cs.bgu.ac.il on 23/11/2019.
//

#include "../include/Action.h"

BaseAction::BaseAction() : errorMsg(""), status(PENDING){}

BaseAction::~BaseAction(){}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    setStatus(COMPLETED);
}

void BaseAction::error(const std::string &errorMsg) {
    setErrorMsg(errorMsg);
    setStatus(ERROR);
    std::cout << errorMsg << std::endl;

}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

void BaseAction::setStatus(ActionStatus s) {
    status=s;
}
void BaseAction::setErrorMsg(std::string s) {
    errorMsg=s;
}
//
// Created by maiy@wincs.cs.bgu.ac.il on 23/11/2019.
//
#include <string>
#include <iostream>
#include <vector>
#include "../include/Action.h"
#include "../include/Session.h"
#include "../include/User.h"
#include <unordered_map>


void DuplicateUser::act(Session& sess){
    std::string input = sess.getInput();
    input = input.substr(8, input.size());
    std::string nameCopy = input.substr(0, input.find(" "));
    std::string myName = input.substr(input.find(" ")+1, input.size()); //decipher user input
    std::unordered_map<std::string, User*>::const_iterator it;
    it = sess.getUserMap().find(nameCopy);
    if(it==sess.getUserMap().end()){ //check if user to duplicate exists
        error("The user does not exist!");
        sess.addActionLog(this);
    }
    else {
        it = sess.getUserMap().find(myName);
        if (it != sess.getUserMap().end()) { //check if new user already exists
            error("A user with this name already exists!");
            sess.addActionLog(this);
        } else {
            sess.duplicateUser(myName, nameCopy);
            complete();
            sess.addActionLog(this);
        }
    }
}

std::string DuplicateUser::toString() const{
    std::string output;
    if (getStatus() == ERROR){
        output = "DuplicateUser: ERROR" + getErrorMsg();
    }

    if (getStatus() == COMPLETED){
        output = "DuplicateUser: COMPLETED";
    }
    if (getStatus() == PENDING){
        output = "DuplicateUser: PENDING";
    }
    return output;
}

BaseAction* DuplicateUser::clone(){
    return (new DuplicateUser(*this));
}

DuplicateUser::~DuplicateUser() {}

#include "../include/Action.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "../include/User.h"
#include "../include/Session.h"

void DeleteUser::act(Session & sess){
    std::string input = sess.getInput();
    input = input.substr(11, input.size()-1);
    std::string name = input.substr(0, input.size()); //decipher user input
    std::unordered_map<std::string, User*>::const_iterator it = sess.getUserMap().find(name);
    if(it==sess.getUserMap().end()){ //check if user exists
        error("The user does not exist!");
        sess.addActionLog(this);
    }
    else{
        if(sess.getActiveUser()->getName()!=name){ //make sure user to delete isnt active user
            User *user = sess.getUserMap().at(name);
            delete(user); //delete user
            sess.deleteUserFromMap(name); //delete in usermap
            complete();
            sess.addActionLog(this);
    }
    }
}
std::string DeleteUser::toString() const{
    std::string output;
    if (getStatus() == ERROR){
        output = "DeleteUser ERROR" + getErrorMsg();
    }
    if (getStatus() == COMPLETED){
        output = "DeleteUser COMPLETED";
    }
    if (getStatus() == PENDING){
        output = "DeleteUser PENDING";
    }
    return output;
}

BaseAction* DeleteUser::clone(){
    return (new DeleteUser(*this));
}

DeleteUser::~DeleteUser() {}
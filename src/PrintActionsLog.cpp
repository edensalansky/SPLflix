#include <string>
#include <iostream>
#include "../include/User.h"
#include "../include/Action.h"
#include "../include/Watchable.h"
#include "../include/Session.h"


void PrintActionsLog::act(Session& sess) {
    std::vector<BaseAction *> actions = sess.getActionsLog();
    for (int i = 0; (unsigned)i < actions.size() ; i++) {
        std::cout << actions.at(i)->toString() << endl;
    }
    complete();
    sess.addActionLog(this);
}
std::string PrintActionsLog::toString() const{
    std::string output;
    if (getStatus() == ERROR){
        output = "PrintActionsLog ERROR" + getErrorMsg();
    }

    if (getStatus() == COMPLETED){
        output = "PrintActionsLog COMPLETED";
    }
    if (getStatus() == PENDING){
        output = "PrintActionsLog PENDING";
    }
    return output;
}

BaseAction* PrintActionsLog::clone(){
    return (new PrintActionsLog(*this));
}

PrintActionsLog::~PrintActionsLog() {}
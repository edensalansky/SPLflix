//
// Created by maiy@wincs.cs.bgu.ac.il on 24/11/2019.
//
#include "../include/Action.h"
#include "../include/Watchable.h"
#include "../include/Session.h"

void PrintContentList::act (Session& sess){
    std::vector<Watchable*> content = *(sess.getContent());
    for (int i=0; (unsigned)i<content.size(); i++){
          std::cout << content.at(i)->toString() << endl;
    }
    complete();
    sess.addActionLog(this);
}
std::string PrintContentList::toString() const{
    std::string output;
    if (getStatus() == ERROR){
        output = "PrintContentList ERROR" + getErrorMsg();
    }
    if (getStatus() == COMPLETED){
        output = "PrintContentList COMPLETED";
    }
    if (getStatus() == PENDING){
        output = "PrintContentList PENDING";
    }
    return output;
}

BaseAction* PrintContentList::clone(){
    return (new PrintContentList(*this));
}

PrintContentList::~PrintContentList() {}
#include <string>
#include <iostream>
#include "../include/User.h"
#include "../include/Action.h"
#include "../include/Watchable.h"
#include "../include/Session.h"

void PrintWatchHistory::act (Session& sess){
    cout<<"Watch history for " << sess.getActiveUser()->getName()<<endl;
    std::vector<Watchable*>* history = sess.getActiveUser()->get_history();
    for (int i=0; (unsigned)i<history->size(); i++){
        string s= history->at(i)->toString();
        s=s.substr(s.find(" "),s.size());
        s=s.substr(0,s.find("["));
        std::cout << i+1<<"."<<s<<endl;
    }
    complete();
    sess.addActionLog(this);

}
std::string PrintWatchHistory::toString() const{
    std::string output;
    if (getStatus() == ERROR){
        output = "PrintWatchHistory ERROR" + getErrorMsg();
    }

    if (getStatus() == COMPLETED){
        output = "PrintWatchHistory COMPLETED";
    }
    if (getStatus() == PENDING){
        output = "PrintWatchHistory PENDING";
    }
    return output;
}

BaseAction* PrintWatchHistory::clone(){
    return (new PrintWatchHistory(*this));
}
PrintWatchHistory::~PrintWatchHistory() {}

//
// Created by edensal@wincs.cs.bgu.ac.il on 24/11/2019.
//

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"

using namespace std;

RerunRecommenderUser::RerunRecommenderUser( string& name):User(name) ,lastId(0){
    setRec("rer");
}
RerunRecommenderUser::RerunRecommenderUser(RerunRecommenderUser &other):User(other), lastId(other.getLastID()){
    setRec(other.getRec());
}
RerunRecommenderUser::~RerunRecommenderUser(){}

void RerunRecommenderUser::addToHistory(Watchable* s){
    history.push_back(s);
}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    Watchable* nextWatchable= history.at(lastId);
    lastId=(lastId+1)%history.size();
    return nextWatchable;
}

User *RerunRecommenderUser::clone() {
    return new RerunRecommenderUser(*this);
}
long RerunRecommenderUser::getLastID() const{
    return lastId;
}





#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"

using namespace std;

LengthRecommenderUser::LengthRecommenderUser(std::string &name) : User(name){
    setRec("len");

}
LengthRecommenderUser::LengthRecommenderUser(LengthRecommenderUser& other):User(other){
    setRec(other.getRec());

}
LengthRecommenderUser::~LengthRecommenderUser() {}


User *LengthRecommenderUser::clone() {
    return new LengthRecommenderUser(*this);
}
void LengthRecommenderUser::addToHistory(Watchable* s){
    history.push_back(s);
};

Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    int avgL=getavgL();
    Watchable* NextWatchable=getNextWatchable(s,avgL);
    return NextWatchable;
}

int LengthRecommenderUser::getavgL() {
    long sum=0;
    for(int i=0;(unsigned)i<history.size();i++)
        sum=sum+(history.at(i)->getLength());
    return sum/history.size();

}

Watchable *LengthRecommenderUser::getNextWatchable(Session &s,int avgL) {
    Watchable* best=s.getContent()->front();
    long min =INTMAX_MAX;
    for ( int i=0; (unsigned)i<s.getContent()->size();i++){
        if (abs((s.getContent()->at(i))->getLength() - avgL) < min)
            if (!findInHistory(s.getContent()->at(i))) {
                best = s.getContent()->at(i);
                min = abs((s.getContent()->at(i))->getLength() - avgL);
            }
    }
    return best;
}

bool LengthRecommenderUser::findInHistory(Watchable * temp) {
    for (vector<Watchable *>::iterator it = history.begin(); it != history.end(); ++it) {
        Watchable* tempT=*it;
        if ((tempT)->getID()==temp->getID())
            return true;
    }
    return false;


}










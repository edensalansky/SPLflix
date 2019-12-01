
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "../include/User.h"
#include "../include/Watchable.h"

#include "../include/Session.h"
using namespace std;
User::User( string &name) : history(), name(name), rec(""){}

std::string User::getName() const{
   return name;
}
User::~User(){
    for(auto &item:history)
       item=nullptr;
    history.clear();
}
User::User(User &other): history(), name(other.getName()),rec(other.getRec()){
    history=vector<Watchable*> ();
  for(int i=0; (unsigned)i<other.get_history()->size();i++)
      history.push_back(other.get_history()->at(i));

  }


vector<Watchable*>* User:: get_history() {
   return &history;
}

void User::addToHistory(Watchable* s) {
    history.push_back(s);

}

void User::setRec(string s) {
    rec=s;
}
string User::getRec() {
    return rec;
}
void User::setName(string s) {
    name=s;
}


#include <string>
#include <vector>
#include <iostream>
#include "../include/Watchable.h"
using namespace std;

Watchable::Watchable(long id, int length, const vector<string>& tags) : id(id),length(length),tags(tags), name(""){

}
Watchable::Watchable (Watchable &other):id(other.getID()),length(other.getLength()),tags(other.getTags()),name(other.getName()) {
    for(auto &item:other.getTags())
           tags.push_back( item);
}


long Watchable:: getID() const {
    return id ;
}
Watchable::~Watchable(){
    tags.clear();
    }

int Watchable::getLength() const{
    return length ;
}
vector<string> Watchable::getTags() const{
    return tags ;
}
string Watchable::getName() const{
    return name;
}


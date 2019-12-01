#include<iostream>
#include "../include/Watchable.h"
#include <string>
#include <vector>
using namespace std;

Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags) : Watchable(id, length, tags), name(name){}

Movie::~Movie(){}
Movie::Movie(Movie &other):Watchable(other.getID(),other.getLength(),other.getTags()), name(other.getName()) {}

string Movie::toString() const {
    string output ="";
    string s = "";
    for (int i=0; (unsigned)i<getTags().size(); i++) {
        s = s + getTags().at(i) + ", ";
    }
    output = output + to_string(this->getID()+1) + ". " + name + " " + to_string(this->getLength()) + " minutes " "[" + s.substr(0,s.length()-2) + "]";
    return output;
}

string Movie::getName() const {
    return this->name;
}

Watchable* Movie::getNextWatchable(Session&) const{
    return nullptr;
}

Watchable* Movie::clone(){
    return (new Movie(*this));
}

string Movie::stringClone(){
    return name;
}

string Movie::nameClone(){
    return name;
}

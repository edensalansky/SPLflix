
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

GenreRecommenderUser::GenreRecommenderUser(std::string &name) : User(name),genre(),maxGenre("default",0){
    setRec("gen");

}
GenreRecommenderUser::GenreRecommenderUser(GenreRecommenderUser& other):User(other), genre(other.getGenre()),maxGenre(other.getMaxGenre()){
    setRec(other.getRec());

}
GenreRecommenderUser::~GenreRecommenderUser(){}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    for (int i = 0; (unsigned)i < s.getContent()->size(); i++) {
        if (!findInHistory(s.getContent()->at(i))) {
            for(string item : (s.getContent()->at(i))->getTags())
                    if(item.compare(maxGenre.first)==0)
                        return (s.getContent()->at(i));
            }
    }
        findNextGenre();
        return getRecommendation(s);

    }

User *GenreRecommenderUser::clone() {
    return new GenreRecommenderUser(*this);
}
void GenreRecommenderUser::findNextGenre() {
    genre.at(maxGenre.first)=-1;
    maxGenre.second=-1;
    for (unordered_map<string,int >::iterator it = genre.begin(); it != genre.end(); ++it) {
        if (maxGenre.second == (*it).second) {// if have the same time of appearance as max put with lex order
            if (maxGenre.first > (*it).first) {
                maxGenre.first = (*it).first;
                maxGenre.second = (*it).second;
            }
        }
            else if(maxGenre.second <(*it).second){
                    maxGenre.first = (*it).first;
                    maxGenre.second=(*it).second;
                }

     }
    }

void GenreRecommenderUser::addToHistory(Watchable* w) {
    vector<string> temp = w->getTags();
    for(int i=0;(unsigned)i<temp.size();i++){
        unordered_map<string,int>::const_iterator got = genre.find (temp.at(i));// check if genre already exist
        if(  got == genre.end() ) {// if no exist
            genre.insert(make_pair(temp.at(i), 1));
         //   history.push_back(w);// add to history
            if(maxGenre.second<1) {
                maxGenre.first = temp.at(i);
                maxGenre.second = 1; }
        }
        else {//exist in genre history
            genre[temp.at(i)]++;
            if(maxGenre.second==genre[temp.at(i)]) {// if have the same time of appearance as max put with lex order
                if(maxGenre.first>temp.at(i)) {
                    maxGenre.first = temp.at(i);
                    maxGenre.second = genre[temp.at(i)]; }
                 }
            if(genre[temp.at(i)]>maxGenre.second) {// time of appearance is larger than max
                maxGenre.first = temp.at(i);
                maxGenre.second=genre[temp.at(i)];}
            }
    }
    history.push_back(w);
}

bool GenreRecommenderUser::findInHistory(Watchable * temp) {
    for (vector<Watchable *>::iterator it = history.begin(); it != history.end(); ++it) {
        Watchable* tempT=*it;
        if ((tempT)->getID()==temp->getID())
            return true;
    }
    return false;
}

unordered_map<string, int> GenreRecommenderUser::getGenre() const{
    return genre;
}
pair<string,int> GenreRecommenderUser::getMaxGenre() const{
    return maxGenre;
}













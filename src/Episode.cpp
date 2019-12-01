#include <string>
#include <vector>
#include "../include/Watchable.h"
#include <iostream>
#include "../include/Session.h"
#include <algorithm>
using namespace std;


Episode::Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags): Watchable(id,length,tags), seriesName(seriesName),season(season),episode(episode),nextEpisodeId(id+1){};

Episode::~Episode(){}

Episode::Episode(Episode &other): Watchable(other.getID(),other.getLength(),other.getTags()),seriesName(other.seriesName),season(other.getSeason()),episode(other.getEpisode()),nextEpisodeId(other.getID()+1){

}


std::string Episode::toString() const{
    string output="";
    string s = "[";
    for (int i =0; (unsigned)i<getTags().size(); i++) {
        s = s + getTags().at(i) + ", ";
    }
    output = output + to_string(this->getID()+1) + ". " + seriesName + " " + to_string(getLength()) + " minutes S" + to_string(season) + "E" + to_string(episode) + " " + s.substr(0,s.length()-2) + "]";
    return output;
}

void Episode::setSeriesName(string other){
    seriesName = other;
}
void Episode::setSeason(int other){
    season = other;
}
void Episode::setEpisode(int other){
    episode = other;
}
string Episode::getName() const {
    return seriesName;
}
int Episode::getSeason() const{
    return season;
}
int Episode::getEpisode() const {
    return episode;
}

Watchable* Episode::getNextWatchable(Session& s) const{

    if(nextEpisodeId == (unsigned)s.getContent()->size()){ //check if we've reached end of content list
        return nullptr;
    }
    if(s.getContent()->at((this->getID()))->nameClone() == (this->getName())) //check if next tv series is the same as current
        return s.getContent()->at(nextEpisodeId);
    else return nullptr;
}

Watchable* Episode::clone(){
    return (new Episode(*this));
}

string Episode::stringClone(){
    string s = seriesName + " " + "S" + to_string(season) + "E" + to_string(episode);
    return s;
}
string Episode::nameClone() {
    return seriesName;
}





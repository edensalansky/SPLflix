#include <vector>
#include <unordered_map>
#include <string>
#include "../include/Action.h"
#include "../include/Session.h"
#include "../include/json.hpp"
#include "../include/Watchable.h"
#include "../include/User.h"
#include <fstream>
using namespace std;
using json = nlohmann::json;


Session::Session(const std::string &configFilePath):content(),actionsLog (),userMap(),activeUser(),terminate(false),input(){
    convertJson(configFilePath);
    string *s= new string ("default");
    User *default1 = new LengthRecommenderUser(*s);
    userMap.insert(make_pair("default",default1));
    setActiveUser(default1);
    delete(s);


}
Session::Session(Session &other): content(), actionsLog(), userMap(), activeUser(), terminate(false), input(){
    copy(other);
}
Session::~Session( ) {
    clear();
}

Session::Session(Session&& other) : content(),actionsLog (),userMap(),activeUser(),terminate(false),input(){
    clear();
    content=*(other.getContent());
    actionsLog=other.getActionsLog();
    userMap=other.getUserMap();
    activeUser=other.getActiveUser();

    for( auto &item : other.content)
                item=nullptr;
    for( auto &item : other.userMap)
        item.second= nullptr;
    other.activeUser= nullptr;
    for( auto &item : other.actionsLog)
        item= nullptr;


}

Session& Session ::operator=( Session& other){
    if(&other==this)
        return *this;
    if(this->content.at(0)!= nullptr)//check if this is empty;
         clear();
    copy(other);
    return *this;
}

Session& Session ::operator=( Session && other) {
    if(&other==this)
        return *this;
    clear();
    content=*(other.getContent());
    actionsLog=other.getActionsLog();
    userMap=other.getUserMap();
    activeUser=other.getActiveUser();
    terminate=false;
    return *this;
}

void Session::clear(){
    for( auto &item : content) {
            delete(item);
            item= nullptr;
    }
    for( auto &item : userMap) {
            delete (item.second);
            item.second = nullptr;

    }
    for( auto &item : actionsLog) {
            delete (item);
            item = nullptr;
    }
    content.clear();
    userMap.clear();
    actionsLog.clear();
    activeUser= nullptr;
    input = "";


}
void Session::copy( Session &other) {
    for (int i = 0; (unsigned)i < other.getContent()->size(); i++) {
        content.push_back((((*other.getContent())[i])->clone()));
    }
    for (int i = 0; (unsigned)i < other.getActionsLog().size(); i++) {
        actionsLog.push_back((other.getActionsLog()[i]->clone()));
    }
    for (auto &item : other.userMap) {
        User *newuser = item.second->clone();
        newuser->get_history()->clear();
        userMap.insert(make_pair(item.first, newuser));
        for (auto &item2 : *item.second->get_history()) {
            newuser->addToHistory(content.at(item2->getID()));
        }
    }
    string temp = other.activeUser->getName();
    activeUser = userMap[temp];
    terminate = false;
    input = other.getInput();
}

void Session::start() {
    std::cout << "SPLFlix is now on!" << endl;
    while (!terminate) {
        getline(cin, input);
        string action;
        if (input.find(" "))
            action = input.substr(0, input.find(" "));
        else {
            action = input;
        }
            if ((action.compare("createuser") == 0) & (input.size()>action.size())) {
                CreateUser *newuser = new CreateUser;
                newuser->act(*this);

            } else if ((action.compare("changeuser") == 0) & (input.size() > action.size())) {
                ChangeActiveUser *changeuser = new ChangeActiveUser;
                changeuser->act(*this);

            } else if ((action.compare("deleteuser") == 0) & (input.size() > action.size())) {
                DeleteUser *deleteuser = new DeleteUser;
                deleteuser->act(*this);


            } else if ((action.compare("dupuser") == 0) & (input.size() > action.size())) {
                DuplicateUser *dupuser = new DuplicateUser;
                dupuser->act(*this);

            } else if (action.compare("log") == 0) {
                PrintActionsLog *actionlog = new PrintActionsLog;
                actionlog->act(*this);


            } else if (action.compare("content") == 0) {
                PrintContentList *printcontent = new PrintContentList;
                printcontent->act(*this);


            } else if (action.compare("watchhist") == 0) {
                PrintWatchHistory *printhistory = new PrintWatchHistory;
                printhistory->act(*this);


            } else if ((action==("watch"))  & (input.size() > action.size())) {
                Watch *watch = new Watch;
                watch->act(*this);


            } else if (action.compare("exit") == 0) {
                Exit *exit = new Exit;
                exit->act(*this);
                terminate = true;
            } else {
                cout << "Invalid input";
            }
        }
    }


std::vector<Watchable*>* Session::getContent() {
    return &content;
}

string Session::getInput()const{
    return input;
}

const vector<BaseAction *> &Session::getActionsLog() const {
    return actionsLog;
}

const unordered_map<std::string, User *> &Session::getUserMap() const {
    return userMap;
}

User *Session::getActiveUser() const {
    return activeUser;
}

void Session::setActiveUser(User *activeUser) {
    Session::activeUser = activeUser;
}
void Session::addActionLog(BaseAction *const action) {
    actionsLog.push_back(action);
}

void Session::addUser(string name, string rec)  {
    if (rec=="len"){
        LengthRecommenderUser *newUser = new LengthRecommenderUser(name);
        userMap.insert(make_pair(name,newUser));
    }
    if (rec=="rer"){
        RerunRecommenderUser *newUser = new RerunRecommenderUser(name);
        userMap.insert(make_pair(name, newUser));
    }
    if (rec=="gen"){
        GenreRecommenderUser *newUser = new GenreRecommenderUser(name);
        userMap.insert(make_pair(name, newUser));
    }
}
void Session::duplicateUser(string myname, string othername){
        std::unordered_map<std::string, User*>::const_iterator it;
        it = userMap.find(othername);
        User *newUser = it->second->clone();
        newUser->setName(myname);
        userMap.insert(make_pair(myname,newUser));

}

void Session::deleteUserFromMap(string name){
    userMap.erase(name);
}

void Session::convertJson(string s){

    std::ifstream i(s);
    json j;
    i >> j;

    //movies
    long id=1 ;
    for (int i = 0; (unsigned)i < j["movies"].size(); i++) {
        const std::string &name = j["movies"][i]["name"];
        int length = j["movies"][i]["length"];
        const std::vector<string> &tags = j["movies"][i]["tags"];
        content.push_back(new Movie(i, name, length, tags));
        id++;
    }
    //tv shows
    id=id-2;
    for (int i = 0; (unsigned)i < j["tv_series"].size(); i++) {
        id++;
        const std::string &seriesName = j["tv_series"][i]["name"];
        int length = j["tv_series"][i]["episode_length"];
        const std::vector<int> &seasons = j["tv_series"][i]["seasons"];
        int season = 0;
        const std::vector<std::string> &tags = j["tv_series"][i]["tags"];
        for (vector<int>::const_iterator it = seasons.begin(); it != seasons.end(); it++) {//
            season++;
            for (int episode = 1; episode <= *it; episode++) {
                content.push_back(new Episode( id,  seriesName, length,  season,  episode , tags));//
                id++;

            }

        }
        id=id-1;
    }

}


void Session::setInput(string s) {
this->input=s;
}

void Session::watchN(){
    Watch *watch = new Watch;
    watch->act(*this);
}
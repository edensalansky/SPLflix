
#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
using namespace std;
class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath);
    Session(Session&);
    Session(Session &&other);
    virtual ~Session();
    Session& operator=( Session &&) ;
    Session& operator=( Session &);
    void start();
    void convertJson(string s);
    std::vector<Watchable*>* getContent()  ;
    const std::vector<BaseAction *> &getActionsLog() const;
    const std::unordered_map<std::string, User *> &getUserMap() const;
    User *getActiveUser() const;
    void setActiveUser(User *activeUser);
    void addActionLog(BaseAction *const action);
    void addUser(string name, string rec) ;
    void duplicateUser(string myname, string othername);
    string getInput()const;
    void copy( Session &other);
    void clear();
    void deleteUserFromMap(string name);
    void setInput(string);
    void watchN();
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    bool terminate;
    string input;
};

#endif
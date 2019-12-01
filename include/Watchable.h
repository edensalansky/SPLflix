#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>


class Session;
using namespace std;
class Watchable{

public:
    Watchable();
    Watchable(long id, int length, const std::vector<std::string>& tags);
    Watchable(Watchable &other);
    virtual ~Watchable();
    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
    virtual Watchable* clone() = 0;
    virtual string stringClone() = 0;
    virtual string nameClone() = 0;
    virtual string getName() const;
    int getLength() const;
    vector<string> getTags() const;
    long getID() const;

private:
    const long id;
    int length;
    std::vector<std::string> tags;
    string name;

};

class Movie : public Watchable{
public:
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    Movie(Movie &);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    virtual Watchable* clone();
    virtual ~Movie();
    virtual string stringClone();
    virtual string nameClone();
    string getName() const;
private:
    std::string name;
};

class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    virtual ~Episode();
    Episode(Episode &other);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    string getName() const;
    void setSeriesName(string other);
    void setSeason(int other);
    void setEpisode(int other);
    int getSeason() const;
    int getEpisode() const;
    virtual Watchable* clone();
    virtual string stringClone();
    virtual string nameClone();

private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;


};

#endif

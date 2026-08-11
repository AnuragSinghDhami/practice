#include<bits/stdc++.h>
using namespace std;

class Observer;

class Subject{

public:

    virtual void attach(Observer* observer) = 0;
    virtual void dettach(Observer* observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() {}
};

class Observer{

public:

    virtual void update(const string& message) = 0;
    virtual ~Observer() {}
};

class NewsAgency : public Subject{

    vector<Observer*> observers;
    string latestNews;
public:

    void attach(Observer* observer){
        observers.push_back(observer);
    }

    void dettach(Observer* observer){
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(){
        for(auto& o : observers){
            o->update(latestNews);
        }
    }

    void setNews(const string& news){
        latestNews = news;
        notify();
    }
};


class NewsChannel : public Observer{

private:

    string name;
public:

    NewsChannel(string n) : name(n) {}

    void update(const string& message) override{
        cout << "[" << name << "] Breaking News: " << message << "\n";
    }
};


int main(){

    NewsAgency* agency = new NewsAgency();

    NewsChannel* channel1 = new NewsChannel("channel 1");
    NewsChannel* channel2 = new NewsChannel("channel 2");

   
    agency->attach(channel1);
    agency->attach(channel2);

    agency->setNews("major tech breakthrough\n");

    agency->dettach(channel1);

    agency->setNews("market");

    delete channel1;
    delete channel2;
    delete agency;
    return 0;
}
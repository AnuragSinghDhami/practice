#include<bits/stdc++.h>
using namespace std;

enum class NotificationType{
    EMAIL, SMS, PUSH
};

class Notification{

public:
    virtual ~Notification() = default;
    virtual void send(const string& message) const = 0;
};

class Email : public Notification{

public :

    void send(const string& message) const override{
        cout << "sending email : " << message << endl;
    }
};

class sms : public Notification{

public :

    void send(const string& message) const override{
        cout << "sending sms : " << message << endl;
    }
};

class NotificationFactory{

public:

    static unique_ptr<Notification> createNotification(NotificationType type){

        switch(type){
            case NotificationType::EMAIL :
                return make_unique<Email>();
            case NotificationType::SMS :
                return make_unique<Email>();
        }
    }
};

int main(){

    
        unique_ptr<Notification> email = NotificationFactory::createNotification(NotificationType::EMAIL);
        email->send("your order has been shipped.");
        cout << "done" << endl;
    
}
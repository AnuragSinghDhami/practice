#include<bits/stdc++.h>
using namespace std;


class PricingStrategy{

public:

    virtual double calculate(int dist, int duration) = 0;
    virtual ~PricingStrategy() = default;
};

class Economy : public PricingStrategy{

public:

    double calculate(int dist, int duration) override{
        return dist * 50 + duration;
    }
};

class Premium : public PricingStrategy{

public:

    double calculate(int dist, int duration) override{
        return dist * 60 + duration;
    }
};

class Carpool: public PricingStrategy{

public:
    double calculate(int dist, int duration) override{
        return dist * 70 + duration;
    }
};

class Book{

private:
    string userid;
    int bookid;
    int dist;
    int duration;
    double fare;

public:

    Book(string& uid, int bid, int distance, int dur, double far){
        userid = uid;
        bookid = bid;
        dist = distance;
        duration = dur;
        fare = far;
    }

    void show_booking(){
        cout << userid << " " << bookid << " " << dist << " " << duration << endl;
    }
};
class BookManager{

private:
    vector<shared_ptr<Book>> bookings;
    int bookingCount = 1;
public:

    shared_ptr<Book> bookRide(string user, int dist, int duration,     unique_ptr<PricingStrategy> price){
        double total = price->calculate(dist, duration);
        auto newBooking = make_shared<Book>(user, bookingCount, dist, duration, total);
        bookingCount++;
        bookings.push_back(newBooking);
        cout << "Booking confiremd of user : " << user << " of distance " << dist << endl;
        return newBooking;
    }
};

int main(){
    BookManager b;
    auto book1 = b.bookRide("anurag", 50, 60, make_unique<Premium>());
    book1->show_booking();
    return 0;
};

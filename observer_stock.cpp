#include<bits/stdc++.h>
using namespace std;

class IObserver{

public:

    virtual ~IObserver() = default;
    virtual void update(string& stock, double stockPrice) = 0;
};

class MobileAppDisplay : public IObserver{

private:
    unordered_set<string> st;
public:
    void setStocks(string s){
        st.insert(s);
    }
    void update(string& stock, double StockPrice){
        if(st.find(stock) != st.end()){
            cout << "updated price of" << stock << "is " << StockPrice << endl;
        }
    }
};

class AutoTradingBot : public IObserver{

private:
    unordered_set<string> st;
public:

    void setStocks(string s){
        st.insert(s);
    }
    void update(string& stock, double StockPrice){
        if(st.find(stock) != st.end()){
            cout << "BOUGHT" << stock << "at " << StockPrice << endl;
        }
    }
};

class Stock{

private:
    vector<IObserver*> observers;
    string stockName;
    double price;

    void notify(){
        for(auto* observer : observers){
            observer->update(stockName, price);
        }
    }
public:

    Stock(string sn, double pr) : stockName(move(sn)), price(pr) {}

    void attach(IObserver* observer){
        observers.push_back(observer);
    }

    void detach(IObserver* observer){
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setPrice(double newPrice){
        price = newPrice;
        notify();
    }
};

int main(){

    MobileAppDisplay mad;
    mad.setStocks("GOOG");
    mad.setStocks("APPL");

    AutoTradingBot atb;
    atb.setStocks("APPL");
    
    Stock stock1("GOOG", 5000);

    stock1.attach(&mad);
    stock1.attach(&atb);
    Stock stock2("APPL", 3000);
    stock2.attach(&mad);
    stock2.attach(&atb);

    stock1.setPrice(6000);
    stock2.setPrice(7000);
    return 0;
}
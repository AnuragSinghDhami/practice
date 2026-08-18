#include<bits/stdc++.h>
using namespace std;

class Beverage{
public:
    virtual ~Beverage() = default;
    virtual double getCost() const = 0;
    virtual string getDescription() const = 0;
};

class BasicCoffee : public Beverage{

public:

    double getCost() const override{
        return 2.0;
    }
    string getDescription() const override{
        return "Basic Coffee";
    }
};

class BeverageWrapper : public Beverage{

protected:
    unique_ptr<Beverage> wrappedBeverage;

public:
    BeverageWrapper(unique_ptr<Beverage> b) : wrappedBeverage(move(b)) {}
};

class Milk : public BeverageWrapper{
public:

    Milk(unique_ptr<Beverage> b) : BeverageWrapper(move(b)) {}

    double getCost() const override{
        return wrappedBeverage->getCost() + 0.5;
    }
    string getDescription() const override{
        return wrappedBeverage->getDescription() + ", Milk";
    }
};
class Sugar : public BeverageWrapper {
public:
    Sugar(std::unique_ptr<Beverage> b) : BeverageWrapper(std::move(b)) {}

    double getCost() const override {
        return wrappedBeverage->getCost() + 0.2;
    }
    std::string getDescription() const override {
        return wrappedBeverage->getDescription() + ", Sugar";
    }
};

int main(){
    unique_ptr<Beverage> myOrder = make_unique<BasicCoffee>();

    //wrap it in milk
    myOrder = make_unique<Milk>(move(myOrder));
    myOrder = make_unique<Sugar>(move(myOrder));

    cout << myOrder->getCost() << endl;
    cout << myOrder->getDescription() << endl;
}
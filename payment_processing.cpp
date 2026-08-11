#include <bits/stdc++.h>
using namespace std;

class PaymentStrategy{

public:

    virtual void pay(double amount) const = 0;  
    virtual ~PaymentStrategy() = default;
};


class PayPal : public PaymentStrategy{

public:

    void pay(double amount) const override{
        cout << "Paid via PayPal\n";
    }
};

class Crpto : public PaymentStrategy{

public:

    void pay(double amount) const override{
        cout << "Paid via Crpto\n";
    }
};

class Item{
private:
    string upcCode;
    double price;
public:

    Item(string upc, double cost) : upcCode(move(upc)), price(cost) {}

    double getPrice() const { return price; }
};

class ShoppingCart{

private:
    vector<Item> items;
public:

    void addItem(const Item& item){
        items.push_back(item);
    }
    double calculationTotal() const{
        double sum = 0;
        for(const auto& item : items){
            sum += item.getPrice();
        }
        return sum;
    }

    void pay(const unique_ptr<PaymentStrategy>& paymentMethod) const{
        double amount = calculationTotal();
        paymentMethod->pay(amount);
    }
};

int main(){
    ShoppingCart cart;
    Item item1("2243", 328);
    Item item2("234", 234);
    cart.addItem(item1);
    cart.addItem(item2);

    cart.pay(make_unique<PayPal>());
    
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

class Burger{

private : 

    int size;
    bool tomato;
    bool cheeze;
    bool toppings;

    Burger(int size) : size(size), tomato(false), cheeze(false), toppings(false) {}
    friend class Builder;

public:

    void printDetail() const{
        std::cout << "Burger size: " << size << " inches"
                  << " | Cheese: " << (cheeze ? "Yes" : "No")
                  << " | toppings: " << (toppings ? "Yes" : "No")
                  << " | tomato: " << (tomato ? "Yes" : "No")
                  << endl;
    }
};

class Builder{

    Burger burger;
public:

    Builder(int size) : burger(size) {}

    Builder& addCheeze(){
        burger.cheeze = true;
        return *this;
    }

    Builder& addToppings(){
        burger.toppings = true;
        return *this;
    }

    Builder& addTomato(){
        burger.tomato = true;
        return *this;
    }

    Burger build(){
        return burger;
    }
};

int main(){

    Burger CustomBurger = Builder(12).addCheeze().addTomato().addToppings().build();

    CustomBurger.printDetail();
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

//step1 - define context class
class VendingMachine;

//step2 - define state interface
class State{

public:

    virtual ~State() = default;
    virtual void insertMoney(VendingMachine* machine, double amount) = 0;
    virtual void selectProduct(VendingMachine* machine, const string& productId) = 0;
    virtual void dispense(VendingMachine* machine) = 0;
    virtual void refund(VendingMachine* machine) = 0;
};

//step 3 - implement context class
class VendingMachine{


private:

    unique_ptr<State> currentState;
    double currentBalance = 0.0;
    unordered_map<string, double> inventoryPrices;
    unordered_map<string, int> inventoryCounts;

public:

    VendingMachine(unique_ptr<State> initialState);

    void changeState(unique_ptr<State> newState){
        currentState = move(newState);
    }

    void addProduct(string id, double price, int count){
        inventoryPrices[id] = price;
        inventoryCounts[id] = count;
    }

    //all behaviour will delegate from here(it is like entry point from public route)
    void insertMoney(double amount){
        currentState->insertMoney(this, amount);
    }
    void selectProduct(string id){
        currentState->selectProduct(this, id);
    }
    void dispense(){
        currentState->dispense(this);
    }
    void refund(){
        currentState->refund(this);
    }


    //state helper methods
    void addBalance(double amount){
        currentBalance += amount;
    }
    double getBalance() const{
        return currentBalance;
    }
    void clearBalance(){
        currentBalance = 0;
    }

    bool isProductAvailable(const string id) { return inventoryCounts[id] > 0; }
    double getProductPrice(const string id) { return inventoryPrices[id]; }
    void releaseProduct(const string id) { inventoryCounts[id]--; }
};

class DispensingState : public State{

private:
    string productId;
public:
    DispensingState(const string& id) : productId(id) {}

    void insertMoney(VendingMachine* machine, double amount) override{
        cout << "Please wait, dispensing in progress\n";
    }

    void selectProduct(VendingMachine* machine, const string& id) override{
        cout << "please wait, dispensing in progress\n";
    }

    void refund(VendingMachine* machine) override{
        cout << "cannot refund during dispending\n";
    }

    void dispense(VendingMachine* machine) override;
};

class HasMoneyState : public State{

public:

    void insertMoney(VendingMachine* machine, double amount) override{
        machine->addBalance(amount);
    }
    void selectProduct(VendingMachine* machine, const std::string& id) override {
        if (!machine->isProductAvailable(id)) {
            std::cout << "Product out of stock.\n";
            return;
        }
        if (machine->getBalance() < machine->getProductPrice(id)) {
            std::cout << "Insufficient funds.\n";
            return;
        }
        std::cout << "Product " << id << " selected.\n";
        machine->changeState(std::make_unique<DispensingState>(id));
        machine->dispense(); // Auto-trigger dispense
    }
    void dispense(VendingMachine* machine) override{
        cout << "select a product first\n";
    }
    void refund(VendingMachine* machine) override;
};

class IdleState: public State{

public:

    void insertMoney(VendingMachine* machine, double amount) override{
        machine->addBalance(amount);
        cout << "inserted " << amount << ". Transitioning to HasMoneyState\n";
        machine->changeState(make_unique<HasMoneyState>());
    } 
    void selectProduct(VendingMachine* machine, const string& id) override{
        cout << "Insert money first\n";
    }
    void dispense(VendingMachine* machine) override {
        std::cout << "Insert money first.\n";
    }
    void refund(VendingMachine* machine) override {
    }
};

//delayed implementation

VendingMachine::VendingMachine(unique_ptr<State> initialState) : currentState(move(initialState)) {}

void HasMoneyState::refund(VendingMachine* machine){
    machine->clearBalance();
    machine->changeState(make_unique<IdleState>());
}

void DispensingState::dispense(VendingMachine* machine) {
    machine->releaseProduct(productId);
    double change = machine->getBalance() - machine->getProductPrice(productId);
    
    std::cout << "Dispensing product: " << productId << "\n";
    if (change > 0) {
        std::cout << "Returning change: " << change << "\n";
    }
    
    machine->clearBalance();
    machine->changeState(std::make_unique<IdleState>());
}


int main(){
    VendingMachine machine(make_unique<IdleState>());

    machine.addProduct("Coke", 1.50, 2);
    machine.addProduct("Chips", 2.00, 1);

    machine.selectProduct("Coke");

    machine.insertMoney(35);
    machine.selectProduct("Coke");
 }


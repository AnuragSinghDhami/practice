#include<bits/stdc++.h>
using namespace std;

class DeliveryFeeStrategy{

public:

    virtual double calculateFee(double distanceKm) const = 0;
    virtual ~DeliveryFeeStrategy() = default;
};

class StandardFeeStrategy : public DeliveryFeeStrategy{

public:

    double calculateFee(double distanceKm) const override{
        return distanceKm* 1.0;
    }
};

class SurgeFeeStrategy : public DeliveryFeeStrategy{

public:

    double calculateFee(double distanceKm) const override{
        return distanceKm* 1.0 + 5.0;
    }
};

class PremiumFeeStrategy : public DeliveryFeeStrategy{

public:

    double calculateFee(double distanceKm) const override{
        return 0.0;
    }
};

enum class OrderStatus{
    PLACED, PREPARING, OUT_FOR_DELIVERY, DELIVERED, CANCELLED
};


class Order{

private:

    string orderId;
    string userId;
    double foodTotal;
    double deliveryFee;
    OrderStatus status;

public:

    Order(string id, string uid, double food, double fee) : orderId(move(id)), userId(move(uid)), foodTotal(food), deliveryFee(fee), status(OrderStatus::PLACED) {}

    void cancel(){
        if(status != OrderStatus::PLACED){
            throw logic_error("Order cannot be cancelled after preparation");
        }
        status = OrderStatus::CANCELLED;
        cout << "Order "<< orderId<< " cancelled successfully";
    }

    void markAsPreparing(){
        if(status != OrderStatus::PLACED){
            throw logic_error("invalid state");
        }
        status = OrderStatus::PREPARING;
        cout << "Order " << orderId << " is now preparing\n";
    }

   void markAsOutForDelivery() {
        if (status != OrderStatus::PREPARING) {
            throw std::logic_error("Invalid state transition to OUT_FOR_DELIVERY.");
        }
        status = OrderStatus::OUT_FOR_DELIVERY;
        std::cout << "Order " << orderId << " is out for delivery.\n";
    }

    void markAsDelivered() {
        if (status != OrderStatus::OUT_FOR_DELIVERY) {
            throw std::logic_error("Invalid state transition to DELIVERED.");
        }
        status = OrderStatus::DELIVERED;
        std::cout << "Order " << orderId << " has been delivered.\n";
    }

    double getTotalPrice() const {
        return foodTotal + deliveryFee;
    }
};

class OrderManager{

private:

    vector<shared_ptr<Order>> activeOrder;
    int orderCounter = 1;

public:

    shared_ptr<Order> checkout(const string& userId, double foodTotal, double distanceKm, unique_ptr<DeliveryFeeStrategy> feeStrategy){

        double fee = feeStrategy->calculateFee(distanceKm);
        string orderId = "ORD-" + to_string(orderCounter++);
        auto newOrder = make_shared<Order>(orderId, userId, foodTotal, fee);
        activeOrder.push_back(newOrder);
        cout << "Checkout complete for " << userId << ". Total: $ " << newOrder->getTotalPrice() <<"\n";
        return newOrder;
    }
};

int main(){

    OrderManager app;
    auto order1 = app.checkout("anurag", 20.0, 10.0, make_unique<StandardFeeStrategy>());

    return 0;
}
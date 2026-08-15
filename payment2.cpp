#include<bits/stdc++.h>
using namespace std;

enum class PaymentStatus{
    PENDING, COMPLETED, FAILED, REFUNDED
};

struct PaymentResult{
    string transactionId;
    PaymentStatus status;
    string errorMessage;

    PaymentResult(string txtId, PaymentStatus s, string err = "") : transactionId(txtId), status(s), errorMessage(move(err)) {}
};

struct Payment{
    double amount;
    string transactionId;
    PaymentStatus status;

    Payment(double amt, string txtId, PaymentStatus s) : amount(amt), transactionId(txtId), status(s) {}
};

string generateId(){
    static mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(100000,999999);
    return "txt-" + to_string(dist(rng));
}

class PaymentStrategy{

public:

    virtual ~PaymentStrategy() = default;
    virtual PaymentResult process(double amount) = 0;
    virtual PaymentResult refund(const string& transactionId, double amount) = 0;
};

class creditCard : public PaymentStrategy{

    string cardNumber;
    string expiryDate;

public:

    creditCard(string card, string expiry) : cardNumber(card), expiryDate(expiry) {}

    PaymentResult process(double amount) override{
        if (cardNumber.length() < 13) {
            return PaymentResult("", PaymentStatus::FAILED, "Invalid card number");
        }
        string txtId = generateId();
        cout << "charged $ " << amount << "to card ending"<< endl;
        return PaymentResult(txtId, PaymentStatus::COMPLETED);
    }
};
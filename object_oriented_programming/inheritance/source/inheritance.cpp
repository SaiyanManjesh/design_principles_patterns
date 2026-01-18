/*
🧩 Problem Statement
You are building an Order Processing System for an e-commerce platform.

Business requirements:
The system must support multiple payment methods.

The order system must:
Initiate a payment
Know whether the payment succeeded or failed

New payment methods must be addable without modifying existing order code.
The order system must not care which payment type is used.

------------------------------------------------------------------------------------------------------------------------------


Thinking:

1. Order   
2. Payments can include many forms like gpay, cards, cash etc

Orders has a payments (composition);
gpay, cards, cash is a payment type (inheritance);

*/

#include <iostream>
#include <unistd.h>
#include <string>

//Local DB
static int total_money = 0;

class IPayment
{
    public:
    virtual ~IPayment() = default;
    virtual bool pay(int amount) = 0;
};


class GpayPayment : public IPayment
{
    public:
    bool pay(int amount) override
    {
        if(amount > 0)
        {
            std::cout<<"Money paid via GPay"<<'\n';
            return true;
        }
        else
        {
            std::cout<<"Money paid via GPay Failed!!!"<<'\n';
            return false;
        }
        
    }
};

class CreditCardPayment : public IPayment
{
    public:
    bool pay(int amount) override
    {
        if(amount > 0)
        {
            std::cout<<"Money paid via CreditCard"<<'\n';
            return true;
        }
        else
        {
            std::cout<<"Money paid via CreditCard Failed!!!"<<'\n';
            return false;
        }
    }
};

// More Payment method can be added later


class Order
{
    public:
    void initate_payment(IPayment& payment, int amount)
    {
        if(payment.pay(amount))
        {
            total_money+=amount;
            std::cout<<"Money transferred successfully!!! and the total amount is: "<<total_money<<'\n';
        }
        else
        {
            std::cout<<"Money transferred Failed!!! and the total amount is: "<<total_money<<'\n';
        }
    }
};


int main()
{
    IPayment* Gpay = new GpayPayment();
    IPayment* CreditCard = new CreditCardPayment();
    Order* Novel = new Order();
    Novel->initate_payment(*Gpay, 100);
    Novel->initate_payment(*CreditCard, -200);
    delete Gpay;
    delete CreditCard;
    delete Novel;

    return 0;
}
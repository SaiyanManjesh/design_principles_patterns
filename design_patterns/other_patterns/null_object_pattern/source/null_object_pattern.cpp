/* 
NULL Object Pattern 

*/



#include <iostream>
#include <string>

class ICustomer
{
    public:
    virtual std::string get_customer_name() = 0;
    virtual void display() = 0;
    virtual  ~ICustomer() = default;
};

class RealCustomer : public ICustomer
{
    private:
    std::string customer_name;

    public:
    RealCustomer(std::string customer_name)
    {
        this->customer_name = customer_name;
    }

    void display() override
    {
        std::cout << "Customer Name: " << customer_name << "\n";
    }

    std::string get_customer_name() override
    {
        return customer_name;
    }
};

class NullCustomer : public ICustomer
{
    private:
    std::string customer_name;

    public:

    std::string get_customer_name() override
    {
        return "No Customer Available!";
    }

    void display() override
    {
        std::cout << "No Customer available!" << "\n";
    }
};

void displayCustomerName(ICustomer* customer)
{
    std::cout << "Customer Name: " << customer->get_customer_name() << std::endl;
}

int main()
{
    ICustomer *manjesh = new RealCustomer("Manjesh");
    ICustomer *patil = new RealCustomer("Patil");
    ICustomer *null_customer = new NullCustomer();

    manjesh->display();
    patil->display();
    null_customer->display();

    delete manjesh;
    delete patil;
    delete null_customer;

    return 0;
}
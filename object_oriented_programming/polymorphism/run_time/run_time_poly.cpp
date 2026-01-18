#include <iostream>
#include <string>

/*

When the base class pointer is pointed to derived class object then the base class function will be called --> static/early/complie time polymorphism
WHY? calling function calling is pointer type not object type


To call the derived class method use virtual method


BASE class
{
    virtual void speak(std::string& mesage) = 0; 
}

dderived class 1
{
    void speak(std::string& mesage)
    {
        bark
    }
}

dderived class 2
{
    void speak(std::string& mesage)
    {
        meow
    }
}

*/

// base class with ABSTRACT method (pure virtual functions)
class Notification {

    public:
    virtual void display() = 0;

};

class EmailNotification: public Notification {

    public:
    void display()
    {
        printf("This is from EMAIL derived class \n");
    }

    void hello()
    {
        printf("This is dummy class \n");
    }
};


class SMSNotification: public Notification {
    public:
    void display()
    {
        printf("This is from SMS Service derived class \n");
    }

};



int main()
{
    Notification* n_ptr = new EmailNotification();
    n_ptr->display(); // This is from EMAIL derived class

    n_ptr = new SMSNotification();
    n_ptr->display(); // This is from SMS Service derived class 

    return 0;
}




//TIP: A good architect uses Abstract method (Pure Virtual functions) in the base class and concrete methods in the dervied class
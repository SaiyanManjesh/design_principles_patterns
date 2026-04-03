#include <iostream>
#include <unistd.h>
#include <unistd.h>
#include <string.h>

// Public and Private constructors example
class single
{
    private:
    single();

    public:
    single(int a)
    {
        std::cout<<"hello "<<a<<"\n";
    }
};


// Constructor Overloading example
class Pizza
{
    private:
    std::string topping1;
    std::string topping2;
    int num_of_toppings = 2;
    public:

    Pizza() {};
    Pizza(std::string  topping1) 
    {
        this->topping1 = topping1;
    }

    Pizza(std::string  topping1, std::string  topping2)
    {
        this->topping1 = topping1;
        this->topping2 = topping2;
    }


    void print()
    {
        std::cout<<this->topping1<<"\n";
        std::cout<<this->topping2<<"\n";
    }

};


// Copy constructor example

class Student
{
    private:
    char  *name;
    int size;


    public:

    Student(char *name)
    {
        size = strlen(name);
        this->name = new char[size + 1];
        strncpy(this->name, name, size);
    }

    //Copy constructor defination
    Student(const Student& other)
    {
        // //shallow copy: Both Objects ka pointer will point to same memory location: no new memory will be created
        // this->name  = other.name;
        // this->size  = other.size;


        //Deep copy: New memory will be created for every heap allocation
        this->name = new char[other.size + 1];
        strncpy(this->name, other.name, other.size);
        this->size  = other.size;
    }

    //Copy constructor deletion
    //Student(const Student& other) = delete;
    void print_name()
    {
        std::cout<<this->name<<"and the memory address is: "<<&this->name<<"\n";
    }
};

int main()
{
    //single a; //default constructor is private and can be accessed inside the class itself
    single s(19); //Parameterised construcrtor can used out the class since it is public
    Pizza A("Peppernoi"); // Parameterised Constructor: useful for assigning values as arguments
    //Pizza b("Mushroom", "Pepper"); Error because Pizza is expecting only 1 arg 
    Pizza B("Mushroom", "Pepper"); // Constructor overloading
    Pizza C;
    A.print();
    B.print();
    C.print();



    Student S1("MANJESH");
    //Student S2(S1); //function "Student::Student(const Student &other)" cannot be referenced -- it is a deleted function
    S1.print_name();
    //S2.print_name(); 

    Student S3(S1);
    S3.print_name();
    return 0;
}


#include <iostream>
#include <unistd.h>


void foo(int &x, int &y) //Passing by reference
{
    std::cout<<"THe a: "<< x<<" address: "<<&x<<" and b:"<<y<<" address: "<<&y<<"\n";
    std::cout<<"THe x: "<< x<<"and y: "<<y<<"\n";
}

void fun1(int *x, int *y) // paasing via pointers
{
    std::cout<<"THe a: "<< *x<<" address: "<<x<<" and b:"<<*y<<" address: "<<y<<"\n";
}

int main()
{

    int a = 1;
    int b = 2;
    int *c = &a;
    int *d = &b;
    std::cout<<"THe a: "<< a<<" address: "<<&a<<" and b:"<<b<<" address: "<<&b<<"\n";

    fun1(c, d);
        // Because *system is an object, not a primitive.
        // std::cout only knows how to print:
        // int
        // float
        // char*
        // etc.
        // Not your custom class.
    foo(a, b); // to do send the reference i need to send the actual address value i.e is a and b
    foo(*c, *d); // here to send the refernece I need to pass the address which is here *c and *d 
    // foo(c, d);

    return 0;
}
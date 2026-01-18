#include <iostream>
#include <unistd.h>


class single
{
    private:
    single();

    public:
    single(int a)
    {
        std::cout<<"hello"<<a<<"\n";
    }
};



int main()
{
    //lsingle a; //default constructor is private and can be accessed inside the class itself
    single s(19); //Parameterised construcrtor can used out the class since it is public

    return 0;
}
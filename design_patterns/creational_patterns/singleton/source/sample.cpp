#include <iostream>
#include <unistd.h>


class Singleton
{
    private: Singleton() {};
    Singleton(Singleton&) = delete; //Deleitng the copy constructor
    Singleton& operator=( Singleton&) = delete; //deleting the assignment constructor

    public:
    int total_calls=0;
    static Singleton& get_instance()
    {
        static Singleton instance;
        std::cout<<"the instance has been called"<<"\n";
        return instance;
    }

    void total_calls_fun()
    {
        total_calls+=1;
        std::cout<<"total calls are"<<total_calls<<"\n";
    }
};


int main()
{
    
    /*Singleton* s1 = Singleton::get_instance();
    s1->get_instance();
    s1->total_calls();

    Singleton* s2 = Singleton::get_instance();
    s2->get_instance();
    s2->total_calls();

    WRONG
    */  
   Singleton::get_instance().total_calls_fun();
   Singleton::get_instance().total_calls_fun();
    return 0;
}


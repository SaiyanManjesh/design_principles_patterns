#include<iostream>
#include<unistd.h>
#include<string>
#include <queue>


class Bulb
{
    public:
    void turn_on_lights()
    {
        std::cout<<"TURNING ON the lights!!!"<<"\n";
    }

    void turn_off_lights()
    {
        std::cout<<"TURNING OFF the lights!!!"<<"\n";
    }

    void dim_down()
    {
        std::cout<<"Dimming down the intensity of the light!"<<"\n";
    }

    void dim_up()
    {
        std::cout<<"Dimming up the intensity of the light!"<<"\n";
    }

};

class ICommand
{
    public:
    virtual ~ICommand() =  default;
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

class LightBulbONCommand : public ICommand
{
    Bulb* bulb;
    public:
    LightBulbONCommand(Bulb *b)
    {
        this->bulb = b;
    }
    void execute() override
    {
        std::cout<<"LIGHT bulb command execute called!"<<"\n";
        this->bulb->turn_on_lights();
    }

    void unexecute() override 
    {
        std::cout<<"LIGHT bulb command unexecute called!"<<"\n";
        this->bulb->turn_off_lights();
    }

};

class LightBulbOFFCommand : public ICommand
{
    Bulb* bulb;
    public:
    LightBulbOFFCommand(Bulb *b)
    {
        this->bulb = b;
    }
    void execute() override
    {
        this->bulb->turn_off_lights();
    }

    void unexecute() override 
    {
        this->bulb->turn_on_lights();
    }
};


class Invoker
{
    public:

    ICommand *on;
    ICommand *off;


    Invoker(ICommand *on, ICommand *off)
    {
        this->on = on;
        this->off = off;

    }

    void turn_on_button()
    {
        this->on->execute();
    }

    void turn_off_button()
    {
        this->off->execute();
    }


};


int main()
{
    Bulb b;
    LightBulbOFFCommand off(&b);
    LightBulbONCommand  on(&b);
    std::cout<<"Address of the b: "<<&b<<"\n";
    std::cout<<"Address of the off: "<<&off<<"\n";
    std::cout<<"Address of the on: "<<&on<<"\n";
    Invoker invoker(&on, &off);
    invoker.turn_on_button();
    invoker.turn_off_button();

    return 0;
}
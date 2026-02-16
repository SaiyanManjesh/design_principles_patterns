/* 
🚦 Problem Statement: Smart Traffic Monitoring System
You are designing a Smart City Traffic Monitoring System.

There is a TrafficSensor that:
Measures vehicle count every second
Measures average speed (future implementation)
When traffic density crosses threshold:

Different systems must react:

🚨 EmergencyControlSystem
→ Turns traffic signals red/green dynamically

📊 AnalyticsDashboard
→ Updates live dashboard

📱 CitizenNotificationApp
→ Sends congestion alert

🚓 PoliceDispatchSystem
→ Sends patrol vehicle if congestion is extreme

----------------------------------------------------------------------------------------------------------------------------------
Thinking:

1. Traffic sensor is an entity (holds vechile count and traffic density) 
    1.a Total number of Vehicles the place can hold (For now I assume a static space)
    1.b When ever the number of vehicles crosses the threshold it should notify to all systems (For now i will assume static threshold)

2. Different systems
    2.a EmergencyControlSystem
    2.b AnalyticsDashboard
    2.c CitizenNotificationApp  (Fow now i will assume 2 systems)
    2.d PoliceDispatchSystem
May be more systems in the future --> Interface for the systems

3. When traffic density crosses threshold all the Systems get react(notify) -> TrafficSensor(PUB) Systems(SUB)

*/

#include <iostream>
#include <unistd.h>
#include <string>

#define MAX_NUMMBER_OF_VEHICLES 10
#define TRAFFIC_DENSITY_THRESHOLD 4
#define MAX_NUMMBER_OF_SYSTEM_CAN_SUBSCRIBE 100


class ISystem
{
    public:
    virtual ~ISystem() = default;
    virtual void update() = 0;
    virtual std::string get_system_name() = 0;

};

class EmergencyControlSystem : public ISystem
{
    private:
    std::string str = "EmergencyControlSystem";
    public:
    void update() override
    {
        std::cout<<"EmergencyControlSystem update called!!! Please Turn the green lights!!!"<<'\n';
    }

    std::string get_system_name() override
    {
        return str;
    }
};

class AnalyticsDashboard : public ISystem
{
    private:
    std::string str = "AnalyticsDashboard";
    public:
    void update() override
    {
        std::cout<<"AnalyticsDashboard update called!!!, Next I will show the live data of number of vehicles"<<'\n';
    }

    std::string  get_system_name() override
    {
        return str;
    }
};

class CitizenNotificationApp : public ISystem
{
    private:
    std::string str = "CitizenNotificationApp";
    public:
    void update() override
    {
        std::cout<<"CitizenNotificationApp update called!!!, You have reach the distination late by 10 mins, more traffic!!!"<<'\n';
    }

    std::string get_system_name() override
    {
        return str;
    }
};



class TrafficSensor
{
    private:
    int number_of_vehicles = 0;
    ISystem *subcribed_systems[MAX_NUMMBER_OF_SYSTEM_CAN_SUBSCRIBE] = {0};
    int index = 0;
    int iterator = 0;

    public:
    //subcribe(system)
    //unsubcribe(system)
    //if number_of_vehicles > threshold -> notify()

    void subcribed_by(ISystem *system)
    {
        std::string current_system_name  = system->get_system_name();
        std::cout<<"The system: "<<current_system_name<<" has been subcribed!"<<"\n";
        //std::cout<<"The subscribed system address is at"<< system <<"\n"; //prints the object memory address
        
        subcribed_systems[index++] = system;
    }

    void unsubcribed_by(ISystem *system)
    {
        std::string current_system_name  = system->get_system_name();
        //Can be done easily via vectors STL
        for(int i = 0; i < index; ++i)
        {
            if(subcribed_systems[i] == system)
            {
                for(int j = i; j < index - 1; ++j)
                {
                    subcribed_systems[j] = subcribed_systems[j + 1];
                }
                subcribed_systems[index - 1] = nullptr;
                index--;
                
                std::cout<<"The system: "<<current_system_name<<" has been unsubcribed!"<<"\n";
                break;
            }
        }

    }


    void update_vechicles()
    {
        number_of_vehicles++;
        std::cout<<"Total number of vehicles are: "<<number_of_vehicles<<'\n';
        notify(); //automactic call
    }

    void notify()
    {
        if(number_of_vehicles > TRAFFIC_DENSITY_THRESHOLD)
        { 
            for(int i = 0; (i < index) && (subcribed_systems[i]!= nullptr); ++i)
            {
                std::cout<<"Notifying system at address: "<< subcribed_systems[i] <<"\n"; //prints all the index address   
                subcribed_systems[i]->update();
            }
        }
    }
};


int main()
{
    TrafficSensor bus_stand_TrafficSensor;
    ISystem *sub1 = new EmergencyControlSystem();
    ISystem *sub2 = new AnalyticsDashboard();
    ISystem *sub3 = new CitizenNotificationApp();

    bus_stand_TrafficSensor.subcribed_by(sub1);
    bus_stand_TrafficSensor.subcribed_by(sub2);
    bus_stand_TrafficSensor.subcribed_by(sub3);
    bus_stand_TrafficSensor.update_vechicles();
    bus_stand_TrafficSensor.update_vechicles();
    bus_stand_TrafficSensor.update_vechicles();
    bus_stand_TrafficSensor.update_vechicles();
    bus_stand_TrafficSensor.update_vechicles();
    bus_stand_TrafficSensor.unsubcribed_by(sub2);
    bus_stand_TrafficSensor.update_vechicles();
    bus_stand_TrafficSensor.subcribed_by(sub2);
    bus_stand_TrafficSensor.update_vechicles();
    


    delete sub1;
    delete sub2;
    delete sub3;
    return 0;
}

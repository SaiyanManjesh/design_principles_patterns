/*
PROBLEM:
One day you decided to create a navigation app for casual travelers. 
The app was centered around a beautiful map which helped users quickly orient themselves in any city.

One of the most requested features for the app was automatic route planning.
A user should be able to enter an address and see the fastest route to that destination displayed on the map.

The first version of the app could only build the routes over roads. People who traveled by car were bursting with joy. 
But apparently, not everybody likes to drive on their vacation. So with the next update, you added an option to build walking routes. 
Right after that, you added another option to let people use public transport in their routes.



Design Thinking:
WHAT TO DO: Navigation app
WHAT will be there:
MAP:
source -> destination
with all the possible routes (having time to travel, distance)
WHAT ARE the possibliteies?
1. Walk
2. bike (2 wheelers)
3. Car (4 wheelers)
Changable componet: Tommorrow new route may be 
*/


#include <iostream>
#include <string>
#include <math.h>
#include <bits/stdc++.h>

class IRoutes
{
    public:
    virtual ~IRoutes() = default;
    virtual std::string get_route_name() = 0;
    virtual int calculate_duration() = 0;

};

class WalkRoute : public IRoutes
{
    public:
    int time_duration;
    int distance;

    std::string get_route_name() override
    {
        return "WALK";
    }

    int calculate_duration() override
    {
        std::srand(time(0));
        return (std::rand());
    }
};

class Wheelers_2_Route : public IRoutes
{
    public:
    int time_duration;
    int distance;

    std::string get_route_name() override
    {
        return "WHeelers 2";
    }

    int calculate_duration() override
    {
        //std::srand(time(0));
        return (std::rand() / 1000);
    }
};


class Wheelers_4_Route : public IRoutes
{
    public:

    
    std::string get_route_name() override
    {
        return "WHeelers 4";
    }
    
    int calculate_duration() override
    {
        //std::srand(time(0));
        return (std::rand() / 10000);
    }
};
// To have one strategy for one Navigation app
class NavigationApp
{
    private:
    std::string source;
    std::string destination;
    std::string route_selection;
    IRoutes* route;


    public:
    void set_routes(IRoutes* route)
    {
        this->route = route;
    }

    void get_directions(std::string source, std::string destination)
    {
        std::cout<<"The posssible directions from source: "<<source<<" to destination: "<<destination<<" are \n";
        std::cout<<"Via "<<route->get_route_name()<<": "<<route->calculate_duration()<<" Seconds."<<"\n";


    }
};

// To have every navigations (not a strategy pattern but can say DI)
// class NavigationApp
// {
//     private:
//     std::string source;
//     std::string destination;
//     std::string route_selection;
//     IRoutes* walkroute;
//     IRoutes* wheelers_2_route;
//     IRoutes* wheelers_4_route;

//     public:
//     void set_routes(IRoutes* walkroute, IRoutes* wheelers_2_route, IRoutes* wheelers_4_route)
//     {
//         this-> walkroute = walkroute;
//         this-> wheelers_2_route = wheelers_2_route;
//         this-> wheelers_4_route = wheelers_4_route;
//     }

//     void get_directions(std::string source, std::string destination)
//     {
//         std::cout<<"The posssible directions from source: "<<source<<" to destination: "<<destination<<" are \n";
//         std::cout<<"Via walk: "<<walkroute->show_route_duration()<<" Seconds."<<"\n";
//         std::cout<<"Via 2 Wheelers: "<<wheelers_2_route->show_route_duration()<<" Seconds."<<"\n";
//         std::cout<<"Via 4 Wheelers:: "<<wheelers_4_route->show_route_duration()<<" Seconds."<<"\n";

//     }
// };


int main()
{

    IRoutes *walk = new WalkRoute;
    IRoutes *wheelers_2 = new Wheelers_2_Route;
    IRoutes *wheelers_4 = new Wheelers_4_Route;
    NavigationApp *gmaps  = new NavigationApp;
    gmaps->set_routes(walk);
    gmaps->get_directions("Nelamangala", "Banglaore");
    gmaps->set_routes(wheelers_2);
    gmaps->get_directions("Nelamangala", "Banglaore");
    gmaps->set_routes(wheelers_4);
    gmaps->get_directions("Nelamangala", "Banglaore");


    delete walk;
    delete wheelers_2;
    delete wheelers_4;
    delete gmaps;
    return 0;
}
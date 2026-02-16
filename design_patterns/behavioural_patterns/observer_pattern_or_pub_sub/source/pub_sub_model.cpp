/*
Problem statement:
Designing a pub_sub model where a OBJECT can be both publisher and subcriber at a same time.


----------------------------------------------------------------------------------------------------------------------------
OBJECT: Engineer
can be a junior, senior, principal etc
He can Publish his knowledge to another Engineer (Pub - notify)
He can Gain knowledege from another Engineer (sub - subscribe)

WHAT HE IS:
1. He as a name
2. He has a list of enginers who he needs to talk
3. He has a list of enginers who he needs to gets knowledge

*/
#include <iostream>
#include <string.h>
#include <unistd.h>

class IEngineer
{
    protected:
    IEngineer *my_subscribers_list[100]; // List where the engineers is subscribed to another 
    IEngineer *my_subscribed_to_list[100]; //List of engineer who im subscribed to //Need to implement
    int my_subscribers_index = 0;
    int my_subscribed_to_index = 0;
    std::string engineer_name;

    public:
    virtual ~IEngineer() = default;

    //set name
    void set_name(std::string name)
    {
        engineer_name = name;
    }
    
    //get the name
    std::string get_name()
    {
        return engineer_name;
    }


    void Subcribed_by(IEngineer *Engineer)
    {
        std::string temp_name = Engineer->get_name();
        std::string curr_eng_name = this->get_name();
        std::cout<<temp_name<<" is subscribed to: "<<curr_eng_name<<" !!!"<<"\n";
        my_subscribers_list[my_subscribers_index++] = Engineer;
    }


    void UnSubcribe_by(IEngineer *Engineer)
    {
        //Need to implement the logic
        for(int i = 0; i<my_subscribers_index; i++)
        {
            IEngineer* temp = my_subscribers_list[i];
            if(temp == Engineer)
            {
                for(int j =i; j<my_subscribers_index - 1;j++)
                {
                    my_subscribers_list[j] = my_subscribers_list[j+1];
                }

                std::cout<<Engineer->get_name()<<" has UNSUBSCRIBED to: "<<this->get_name()<<"\n";
                my_subscribers_list[my_subscribers_index - 1] = NULL;
                my_subscribers_index--;
                break;
            }
        }

    }

    void Notify()
    {
        //std::cout<<"Notify has been called"<<"\n";
        for(int i = 0; i<my_subscribers_index; ++i)
        {
            std::cout<<my_subscribers_list[i]->get_name()<<"\n";
            my_subscribers_list[i]->Update();
        }
    }

    void get_subscribers_list()
    {
        //std::cout<<"get_subscribers_list has been called"<<"\n";
        std::cout<<"The list of subscribers for "<< this->get_name() <<" are: "<<"\n";
        for(int i=0; i< my_subscribers_index; i++)
        {
            std::string curr_eng_name = my_subscribers_list[i]->get_name();
            std::cout<< curr_eng_name <<"\n";
        }
    }

    virtual void Update() = 0;

};


class SENIOREngineer : public IEngineer
{

    public:
    void Update() override
    {
        std::cout<<"Senior Engineer!!! Udpate has been called!"<<"\n";
    }



};


class JUNIOREngineer : public IEngineer
{
    //update
    void Update() override
    {
        std::cout<<"Junior Engineer!! AN Update has been called !!!"<<"\n";
    }

};


int main()
{
    IEngineer *senior1  = new SENIOREngineer();
    IEngineer *senior2  = new SENIOREngineer();
    IEngineer *senior3  = new SENIOREngineer();
    senior1->set_name("DAVID MALAN");
    senior2->set_name("BOB MAtrin");
    senior3->set_name("Gamma Erich");

    IEngineer *junior1  = new JUNIOREngineer();
    IEngineer *junior2  = new JUNIOREngineer();
    IEngineer *junior3  = new JUNIOREngineer();
    junior1->set_name("Manjesh patil");
    junior2->set_name("Patrick Batmen");
    junior3->set_name("Bruce Wayne");

    senior1->Subcribed_by(junior1);
    senior1->Subcribed_by(junior2);
    senior1->Subcribed_by(junior3);
    senior2->Subcribed_by(junior1);
    senior3->Subcribed_by(junior1);
    junior2->Subcribed_by(junior1);
    junior3->Subcribed_by(junior1);


    senior1->Subcribed_by(junior2);
    senior2->Subcribed_by(junior2);


    senior2->Subcribed_by(junior2);
    senior3->Subcribed_by(junior3);
    senior2->UnSubcribe_by(junior2);

    senior1->Notify();
    senior1->get_subscribers_list();
    senior2->Notify();


    delete senior1;
    delete senior2;
    delete senior3;
    delete junior1;
    delete junior2;
    delete junior3;



    return 0;
}
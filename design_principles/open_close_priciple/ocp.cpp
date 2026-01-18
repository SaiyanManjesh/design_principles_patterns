/*
Problem statement: Build a Notification system that sends messages via:
Email
SMS
(Later) WhatsApp, Push, etc.

Understanding
1. How to send => via notification
2. When/why to send => to get the notification
3. What to send => whatsapp, twitter
*/


#include <iostream>
#include <string>


// Old code without OCP 
// class NotificationService {
// public:
//     void send(const std::string& type, const std::string& message) {
//         if (type == "EMAIL") {
//             printf("This is from Email service \n");
//         }
//         else if (type == "SMS") {
//             printf("This is from SMS service \n");
//         }
//         // Tomorrow:
//         // else if (type == "WHATSAPP") { ... }
//     }
// };



//Now via OCP principle
class Notification {

    public:
    virtual ~Notification() = default;
    virtual void send(const std::string & message) = 0;

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

    void send(const std::string& message) override
    {
        std::cout << "Message sent via Email: " << message << std::endl;
    }
};

class SMSNotification: public Notification {


    public:

    void send(const std::string& message) override
    {
       std::cout << "Message sent via SMS: " << message << std::endl;
    }
};

// In future i can add for whatsapp, twitter etc...



// Abstraction
class NotificationService {
public:
    void notify(Notification& notification, const std::string& message) {
        notification.send(message);
        // Next here I can add log, validate etc which will be common for all the type of service.
    }
};



int main() {
    // // calling via the stack
    // NotificationService service;
    // service.send("EMAIL", "Hello");

    // // calling via pointers
    // NotificationService* ser = new NotificationService();
    // ser->send("SMS", "Hello from SMS");

    Notification* noti_ptr = new EmailNotification();
    noti_ptr->send("My mail is manjesh@gmail.com");
    Notification* SMS =  new SMSNotification();
    SMS->send("OTP: 1234");

    // Proper OCP

    NotificationService service;

    EmailNotification email;
    SMSNotification sms;

    service.notify(email, "Order confimed");
    service.notify(sms, "OTP: 1234");
    return 0;
}

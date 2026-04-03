/*
Problem — Chat Application Emoji System
You are building:
WhatsApp / Slack style chat
Users send:
😀 😀 😀 😀 😀 😀 😀 😀 😀
Thousands of messages.

Naive Design
Each emoji stores:
image
unicode
metadata
size
color

If:
1 million emojis
Memory explodes.

Flyweight Design

Create:
EmojiType (Flyweight)
    unicode
    image
    metadata

Then:
EmojiMessage
    position
    timestamp
    reference to EmojiType

Architecture

EmojiFactory
    Map<unicode, EmojiType>


Reuse emoji objects

-----------------------------------------------------------------------------------------------------------------------------

Design Thinking:
Every emoji has its own unicode
For this emoji 😀: 0xF0 0x9F 0x98 0x80 -> shared everywhere = Flyweight
I need to have a message where the emoji reference should be present;
*/


#include <iostream>
#include <string>
#include <map>
// 1. way to do -> use interface 
// class EmojiType
// {
//     public:
//     virtual void use_emoji();
// };

// 2. way to do -> factory method to create the required objects
class EmojiType
{
    public:
    std::string unicode;

    EmojiType(const std::string& unicode)
    {
        this->unicode = unicode;
    }
    std::string get_emoji()
    {
        return unicode;
    }

};

// So for every message end im putting the emoji
class Message
{
    private:
    std::string message_context;
    int position;
    EmojiType* emoji;

    public:

    void write_context(const std::string& message, int position, EmojiType* emoji)
    {
        this->message_context = message;
        this->position = position;
        this->emoji = emoji;
        std::cout
            << message_context
            << emoji->get_emoji()
            << "\n";
    }


};

// Creates a shared object of a required emojis
class EmojiFactory
{
    private:
    std::map<std::string, EmojiType*> emojis;

    public:
    EmojiType* create_emoji(const std::string& unicode)
    {
        if(emojis.find(unicode) == emojis.end())
        {
            emojis[unicode] = new EmojiType(unicode);
        }
        return emojis[unicode];
    }
    
};


int main()
{
    EmojiFactory* emojifactory = new EmojiFactory();
    EmojiType*laughing_emoji = emojifactory->create_emoji("😀");
    EmojiType*laugh_loud_emoji = emojifactory->create_emoji("😂");
    EmojiType* heart_emoji = emojifactory->create_emoji("❤️");
    EmojiType* thumbsup_emoji = emojifactory->create_emoji("👍");
    EmojiType* fire_emoji = emojifactory->create_emoji("🔥");
    

    Message* hello_world  = new Message();
    hello_world->write_context("Hello world", 10,laughing_emoji);

    Message *manjesh  = new Message();
    manjesh->write_context("manjesh", 0000,laugh_loud_emoji);
    manjesh->write_context("manjesh", 1000,heart_emoji);
    manjesh->write_context("manjesh", 2000,thumbsup_emoji);
    manjesh->write_context("manjesh", 300,fire_emoji);
    manjesh->write_context("manjesh", 500,laughing_emoji);


    delete emojifactory;
    delete hello_world;
    delete manjesh;
    delete laughing_emoji;
    delete laugh_loud_emoji;
    delete heart_emoji;
    delete thumbsup_emoji;
    delete fire_emoji;
    return 0;
}
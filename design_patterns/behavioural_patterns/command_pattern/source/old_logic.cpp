/*
PROBLEM STATEMENT:

Design and implement a mini text editor core engine in C++ using the Command Pattern.

🎯 Requirements
You must design a text editing engine that supports:

1️⃣ Basic Editing
Insert text at position
Delete text from position
Replace text

2️⃣ Undo / Redo
Unlimited undo
Unlimited redo
Proper state restoration


3️⃣ Logging
Every executed command must be logged.
[10:21] Insert "Hello" at position 0
[10:22] Delete 3 chars at position 5

4️⃣ Deferred Execution
Commands can be queued and executed later.
Example:
Batch editing script
Background execution
----------------------------------------

EXPECTED SYSTEM BEHAVIOR

Your system must support scenarios like:

Insert("Hello")
Insert(" World")
Undo()
Redo()

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Design Thinking:
Core Engine(Receiver)
1. insert text
2. delete text
3. replace text


Commands
1. Insert text: execute, unexecute
2. delete text: execute, unexecute
3. Repalce text: execute, unexecute

Application: Notepad(Invoker)
click and unclick button with logging
*/


#include<iostream>
#include<string>
#include <string.h>
#include<queue>
#include<deque>
#include <stack>

class CoreEngine
{
    FILE *file = NULL;
    char file_buffer[1000] = {0};
    char name_of_file[50] = {0};
    int cursor = -1;

    public:
    CoreEngine(char *file_name)
    {
        int length = strlen(file_name);
        strncpy(name_of_file, file_name, length);
        memset(&file_buffer, 0, sizeof(file_buffer));
        this->cursor = 0;
    }

    bool add_text(char *text)
    {
        if(text == NULL)
        {
            std::cout<<"Text is empty! Cannot add!"<<"\n";
            return false;
        }

        int text_length = strlen(text);
        strncpy(file_buffer, text-1, text_length-1);
        this->cursor+= text_length;
        return true;
    }

    bool delete_text(int delete_length)
    {
        if(delete_length > this->cursor)
        {
            std::cout<<"Cannot delete more than the current words!"<<"\n";
            return false;
        }

        int it_length = delete_length;
        int start_delete_pos = this->cursor - delete_length;

        for(int i = start_delete_pos; i < strlen(file_buffer); ++i)
        {
            file_buffer[i] = file_buffer[i+1];
        }
        this->cursor = it_length;
    }

};


//Commands

class ICommands
{
    
    public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};


class AddTextCommand : public ICommands
{
    CoreEngine *Engine_1;
    char *insert_text;
    public:
    AddTextCommand(CoreEngine *eng, char *text)
    {
        memset(insert_text, 0, sizeof(insert_text));
        this->Engine_1 = eng;
        strncpy(insert_text, text, strlen(text));
    }

    void execute() override
    {
        this->Engine_1->add_text(insert_text);
    }

    void undo() override
    {
        this->Engine_1->delete_text(strlen(insert_text));
    }

};


//invoker

class Buttons
{
    std::deque<ICommands *> command_list;
    std::stack<ICommands *> executed_commands;
    ICommands *cmd_1;
    public:
    Buttons(ICommands *cmd)
    {
        command_list.push_back(cmd);
        this->cmd_1 = cmd;
    }

    void click_me_1()
    {
        this->cmd_1->execute();
        executed_commands.push(this->cmd_1);

    }
    void click_me_2()
    {
        ICommands *temp;
        temp = executed_commands.top();
        temp->undo();
        executed_commands.pop();
    }
};



int main()
{

    CoreEngine *e1 = new CoreEngine("Manjesh.txt");
    ICommands *add_cmd_1 = new AddTextCommand(e1, "hello");
    ICommands *add_cmd_2= new AddTextCommand(e1, " Worlld");
    ICommands *add_cmd_3= new AddTextCommand(e1, " ASP!!!");
    
    Buttons *b1= new Buttons(add_cmd_1);
    b1->click_me_1();


    return 0;
}
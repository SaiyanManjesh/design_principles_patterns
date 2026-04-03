/*
🎯 Objective

Design a system that processes financial transactions using the Command Pattern.

The system must support:
Executing transactions
Undoing transactions
Logging transaction history
Scheduling transactions

🧱 Core Domain
You must model:

1️⃣ BankAccount (Receiver)
Each account should support:
Deposit(amount)
Withdraw(amount)
Transfer(toAccount, amount)
View balance
BankAccount must not know anything about commands.

🧱 Commands
Each financial operation must be implemented as a command:
DepositCommand
WithdrawCommand
TransferCommand
Each command must:
Store necessary state
Execute the transaction
Support undo

Example:
If WithdrawCommand executes ₹500,
Undo must restore ₹500.

🧠 Business Rules
Withdraw cannot exceed balance.
Transfer must fail if insufficient funds.
Undo must restore previous state safely.
Failed commands must not enter undo history.

🏗 TransactionManager (Invoker)
Create a central manager responsible for:
Executing commands
Maintaining undo stack
Maintaining redo stack
Logging all successful transactions
Clearing redo stack when new transaction occurs
TransactionManager must only depend on Command interface.
It must not directly manipulate BankAccount logic.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Thinking:
Executing transactions: Transfer, withdraw, deposit
Undoing transactions
Logging transaction history
Scheduling transactions
To execute all the commands we need 2 things 
Who invokes (Transaction Manager)
Who will receive it (Bank Account)

*/

#include<iostream>
#include<string>
#include <string.h>
#include<queue>
#include<deque>
#include <stack>

/*

Each account should support:
Deposit(amount)
Withdraw(amount)
Transfer(toAccount, amount)
View balance

*/
class BankAccount
{
    private:
    char account_holder_name[100];
    int amount = 0;

    public:
    BankAccount(char *name, int deposit_amount)
    {
        strncpy(this->account_holder_name, name, sizeof(this->account_holder_name) - 1);
        this->account_holder_name[sizeof(this->account_holder_name) - 1] = '\0';
        this->amount = deposit_amount;
    }

    const char* get_account_name()
    {
        return this->account_holder_name;;
    }

    void deposit(int amount)
    {
        std::cout<<"Depositing amount: "<<amount<<" to account: "<<account_holder_name<<"\n";
        this->amount+=amount;
    }

    int view_balance()
    {
        return this->amount;
    }

    int withdraw_amount(int amount)
    {
        int current_amount = this->amount - amount;
        if(this->amount < amount)
        {
            std::cout<<"Cannot Withdraw!! Money is less than the required amount!!!"<<"\n";
            return -1;
        }

        this->amount = current_amount;
        return current_amount;
    }

    void transfer_money(BankAccount *receiver_bank_acc,  char *to_name, int amount)
    {
        //For now im just checking the amount not name in the database
        int remaining_amount = this->amount - amount;
        if(this->amount < amount)
        {
            std::cout<<"Cannot Transfer!!! money is less than transferrable amount!!"<<"\n";
            return;
        }
        std::cout<<"The amount of: "<<amount<<" Has been transfferd to: "<<to_name<<" \n";
        receiver_bank_acc->amount+=amount;
        this->amount = remaining_amount;

    }

    void receive_money(BankAccount *sender_bank_acc, const char *from_name, int amount)
    {
        std::cout<<"The amount of: "<<amount<<" had been transfferd from: "<<from_name<<"\n";

        std::cout<<"Semder has :"<<sender_bank_acc->amount<<"\n";
        if(sender_bank_acc->amount < amount)
        {
            std::cout<<"Semder has less money to send!!!"<<"\n";
            return;
        }
        sender_bank_acc->amount -=amount;
        this->amount +=amount;
    }
};



class ICommand
{
    public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void unexecute() = 0;
    //virtual void undo() = 0;
};

class DepositCommand : public ICommand
{
    BankAccount *bankacc;
    int amount = 0;
    
    public:
    DepositCommand(BankAccount *bankacc, int amount)
    {
        this->bankacc = bankacc;
        this->amount = amount;
    }

    void execute() override
    {
        bankacc->deposit(amount); 
    }

    void unexecute() override
    {
        bankacc->withdraw_amount(amount);
    }

};


class TransferMoneyCommand : public ICommand
{
    BankAccount *sender_bankacc;
    BankAccount *receiver_bankacc;
    int amount = 0;
    char to_name[100];
    char from_name[100];
    public:
    TransferMoneyCommand(BankAccount *s_bankacc,BankAccount *r_bankacc, char *to_name, int amount)
    {
        this->sender_bankacc = s_bankacc;
        strncpy(this->to_name, to_name, sizeof(this->to_name) - 1);
        this->to_name[sizeof(this->to_name) - 1] = '\0';
        this->receiver_bankacc = r_bankacc;
        this->amount = amount;
    }

    void execute() override
    {
        this->sender_bankacc->transfer_money(this->receiver_bankacc, to_name, amount); 
    }

    void unexecute() override
    {
        this->sender_bankacc->receive_money(this->sender_bankacc,  to_name, amount);
    }

};

class ViewMoneyCommand : public ICommand
{
    BankAccount *bankacc;
    int balance = 0;
    public:
    ViewMoneyCommand(BankAccount *bankacc)
    {
        this->bankacc = bankacc;
    }

    void execute() override
    {
        balance = bankacc->view_balance();
        std::cout<<bankacc->get_account_name()<<" : Your balance is : "<<balance<<"\n";
    }

    void unexecute() override
    {
        std::cout<<"VIEW balace UNDO Called!!!"<<"\n";
    }
};

//In future I can extend this for LoggingOperation, AnyaliticsOperations etc etc So that it will be easy to add a new class rather than modifying in the existing class

// So The thing is
/*
How to store the comamnds?
1. Store the executed commands: Good because 
2. Store it and at the end execute it: This will be complete execution at once-> undo will be difficult for one, 2 times

*/
class TransactionManager
{
    public:
    std::deque <ICommand*> command_execution_list_queue;
    std::vector<ICommand*> command_list;
    ICommand *command;
    // ICommand *DepositCommand;
    // ICommand *TransferMoneyCommand;
    // ICommand *ViewMoneyCommand;
    void click_button(ICommand *command)
    {
        command->execute();
        command_execution_list_queue.push_back(command);
    }

    void unclick_button()
    {
        command = command_execution_list_queue.back();
        command->unexecute();
        command_execution_list_queue.pop_back();
    }

};


int main()
{

    char name1[100] = "MANJESH";
    char name2[100] = "HARLEY";
    

    BankAccount *account_1 = new BankAccount(name1, 100);
    BankAccount *account_2 = new BankAccount(name2, 1000);

    ICommand *depositmoney = new DepositCommand(account_1, 500);
    ICommand *transfermoney = new TransferMoneyCommand(account_1,account_2, name2, 300);
    ICommand *viewbalance  = new ViewMoneyCommand(account_1);

    TransactionManager *TM = new TransactionManager();

    // while(1)
    // {
    //     std::cout<<"What needs to be done!"<<"\n";
        
    // }
    TM->click_button(depositmoney);
    TM->click_button(viewbalance);
    TM->click_button(transfermoney);
    TM->click_button(viewbalance);
    TM->click_button(new TransferMoneyCommand(account_1, account_2, name2, 400));
    TM->click_button(viewbalance);
    TM->click_button(new TransferMoneyCommand(account_2, account_1, name1, 100));
    TM->click_button(viewbalance);
    TM->unclick_button();
    TM->unclick_button();
    TM->click_button(viewbalance);
    // deposit->execute();
    // transfermoney->execute();

    return 0;
}
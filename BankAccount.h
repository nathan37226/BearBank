/*
Group Members: Nathan Obert M03134502, Keegan Maynard 
*/
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>
using namespace std;

class BankAccount
{
private:
    string accountNum;
    double balance;
    double intRate;
    double serCharge;

public:
    BankAccount(string actNum, double bal, double rate);
    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    void calcInt();
    void yearlyCharge();
    void closeAct();

};
#endif
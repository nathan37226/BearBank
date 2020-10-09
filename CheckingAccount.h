/*
Group Members: Nathan Obert M03134502, Keegan Maynard 
*/
#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
#include <string>
#include <iostream>
#include "BankAccount.h"
using namespace std;

class CheckingAccount : public BankAccount
{
private:
    string flag;
    void nsfCharge();

public:
    CheckingAccount(string actNum, double bal, double rate, int risk);
    void deposit(double amount);
    void withdraw(double amount);
    void closeAcc();
    void setRisk(int option);
};

CheckingAccount::CheckingAccount(string actNum, double bal, double rate, int risk) : BankAccount(actNum, bal, rate) 
{
    setRisk(risk); //low risk initially
}

void CheckingAccount::setRisk(int option)
{
    try
    {
        switch (option)
        {
            case 1:
            {
                flag = "Low Risk";
                break;
            }
            case 2:
            {
                flag = "High Risk";
                break;
            }
            default:
            {
                string error = "Invalid argument: setRisk expects 1 or 2, got passed the value " + to_string(option);
                throw error;
            }
        }
    }
    catch (string err)
        {
            cout << err << endl;
        }
}

void CheckingAccount::deposit(double amount)
{
    ;
}

void CheckingAccount::withdraw(double amount)
{
    ;
}

void CheckingAccount::closeAcc()
{
    ;
}
#endif
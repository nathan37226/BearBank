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
    CheckingAccount(string actNum, double bal, double rate);
    void deposit(double amount);
    void withdraw(double amount);
    void closeAcc();
    void setRisk(int option);
};

CheckingAccount::CheckingAccount(string actNum, double bal, double rate) : BankAccount(actNum, bal, rate) 
{
    ;
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
                if (accountNum.substr(0,1) == "*")
                    accountNum = accountNum.substr(1, string::npos); //getting rid of *, which denotes high risk
                break;
            }
            case 2:
            {
                flag = "High Risk";
                if (accountNum.substr(0,1) != "*")
                    accountNum = "*" + accountNum; //adding high risk marker to the act num
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

    cout << accountNum << endl;
}

void CheckingAccount::deposit(double amount)
{
    try
    {
        if (amount < 0.0)
        {
            string error = "Invalid argument: you cannot deposit a negative amount";
            throw error;
        }
        else if (amount <= 9999.0)
        {
            setBal( getBal() + amount );
        }
        else
        {
            setBal( getBal() + amount );
            setRisk(2); // since more than $9999.00 deposited, must flag acct as high risk
        }
    }
    catch (string err)
    {
        cout << err << endl;
    }
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
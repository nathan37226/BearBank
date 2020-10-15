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
    CheckingAccount(){}
    CheckingAccount(string actNum, double bal, double rate);
    string deposit(double amount);
    string withdraw(double amount);
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
        string actNum = getActNum(); //for easier access later

        switch (option)
        {
            case 1:
            {
                flag = "Low Risk";
                if (actNum.substr(actNum.length() - 1, string::npos) == "*") //comparing to last char of the actNum
                {
                    setActNum( actNum.substr(0, actNum.length() - 1) ); //getting rid of *, which denotes high risk
                }
                break;
            }
            case 2:
            {
                flag = "High Risk";
                if (actNum.substr(actNum.length() - 1, string::npos) != "*") //comparison with last char
                {
                    setActNum( actNum + "*" ); //adding high risk marker to the act num
                }
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

string CheckingAccount::deposit(double amount)
{
    if (isOpen())
    {
        try
        {
            if (amount < 0.01)
            {
                string error = "Invalid argument: you cannot deposit a negative amount";
                throw error;
            }
            else if (amount <= 9999.0) //will not flag account
            {
                setBal(getBal() + amount);
            }
            else
            {
                setBal(getBal() + amount);
                setRisk(2); // since more than $9999.00 deposited, must flag acct as high risk
            }
        }
        catch (string err)
        {
            cout << err << endl;
        }
        string amnt = to_string(amount);
        amnt = amnt.substr(0, amnt.length() - 4); //takes off the "0000" at the end of the double
        return "You have successfully deposited $" + amnt + " into your account.";
    }
    else
    {
        return "The account is currently closed\n";
    }
    
}

void CheckingAccount::nsfCharge()
{
    setBal( getBal() - 25.00 ); //always a 25.00 fee
}

string CheckingAccount::withdraw(double amount)
{
    if (isOpen())
    {
        try
        {
            if (amount < 0.0)
            {
                string error = "Invalid Argument: cannot withdraw less than $0.00";
                throw error;
            }
        }
        catch (string err)
        {
            cout << err << endl;
        }

        double newBal = getBal() - amount;

        if (newBal < 0.0)
        {
            if (getBal() >= 25.00) //i.e. can pay the fee without going neg
            {
                nsfCharge(); //only charge fee, and the wanted withdraw will be discarded
            }
            else //i.e. paying the nsf fee will make account go negative
            {
                nsfCharge(); //this will technically allow for infinite nsf fee's, so there should be a stop implemented sometime
                setRisk(2);
            }
            return "You do not have suffient funds to withdraw $" + displayNum(amount) + ".\nYou have incurred a $25.00 non-sufficent fund fee.";
        }
        else
        {
            setBal(newBal); //no fees to charge, so this is a good withdrawl
        }
        return "You have withdrawn $" + displayNum(amount) + " from you account.";
    }
    else
    {
        return "The account is currently closed\n";
    }
}

void CheckingAccount::closeAcc()
{
    setIsClosed(true);
}
#endif
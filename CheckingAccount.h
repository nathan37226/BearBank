/*
Group Members: Nathan Obert M03134502 and Keegan Maynard M03114078
This header file creates the Checking Account and its behaviors. The account is a child of BankAccount, so it inherits some of its 
members and functions. The CheckingAccount includes private members to store the risk of an account and a charge non-sufficient
fund fees, public methods to initialize the account, deposit and withdraw money, closs the account, and set the risk, 
as well as a constructor to initialize the account.
All of these methods and members are used to keep track of the balance of the account, allow the user to add or remove money from the 
account, charge a fee if the account has a negative balance, define risk for bad withdrawls, and close the account. 
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
    void nsfCharge(); //always charges a 25.00 fee

public:
    CheckingAccount(){} //basic constructor
    CheckingAccount(string actNum, double bal, double rate);
    string deposit(double amount);
    string withdraw(double amount);
    void closeAcc();
    void setRisk(int option);
};

CheckingAccount::CheckingAccount(string actNum, double bal, double rate) : BankAccount(actNum, bal, rate) 
{
    flag = "Low Risk"; //low risk initially
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
                throw "Invalid argument: setRisk expects 1 or 2, got passed the value " + to_string(option);
            }
        }
    }
    catch (string err)
        {
            cout << err << endl;
        }

}

void CheckingAccount::nsfCharge()
{
    setSerCharge(25.00);
    performSerCharge(); //technically this will allow for an infinite negative balance to accumulate, but fiscal responsibility is also important on the user's part
}

string CheckingAccount::deposit(double amount)
{
    if (isOpen()) //only if open is the acct able to deposit
    {
        try
        {
            if (amount < 0.01)
            {
                throw "Invalid argument: you cannot deposit a negative amount";
            }
            else 
            {
                if (amount <= 9999.0) //will not flag account
                {
                    setBal(getBal() + amount);
                }
                else
                {
                    setBal(getBal() + amount);
                    setRisk(2); // since more than $9999.00 deposited, must flag acct as high risk
                }
                
                return "You have successfully deposited $" + BankAccount::displayNum(amount) + " into your account.";
            }
        }
        catch (string err)
        {
            return err;
        }
    }
    else
    {
        return "The account is currently closed\n";
    }
    
}

string CheckingAccount::withdraw(double amount)
{
    if (isOpen()) //only if open is the acct able to withdraw
    {
        try
        {
            if (amount < 0.0)
            {
                throw "Invalid Argument: cannot withdraw less than $0.00";
            }
        }
        catch (string err)
        {
            return err;
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
/*
Group Members: Nathan Obert M03134502, Keegan Maynard 
*/
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>
#include <cmath>
using namespace std;

class BankAccount
{
private:
    string accountNum;
    double balance;
    double intRate;
    double serCharge;

    double roundNum(double value, int decimal);

public:
    BankAccount(){}
    BankAccount(string actNum, double bal, double rate);
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    void calcInt();
    void yearlyCharge();
    virtual void closeAcc() = 0;

    //setter and getter functs, for derived class use
    void setActNum(string num);
    string getActNum();
    void setBal(double bal);
    double getBal();

};

BankAccount::BankAccount(string actNum, double bal, double rate)
{
    accountNum = actNum;
    balance = bal;
    intRate = rate;
}

void BankAccount::yearlyCharge()
{
    balance -= serCharge; //check for once in a calendar year!
}

double BankAccount::roundNum(double value, int decimal)
{
    double multiplier = pow(10, decimal);
    value = value * multiplier; //makes so the integer part will have all the numbers wanted

    int tempValue = value; //cuts off extra decimal part
    int higherTempValue = tempValue + 1; //in case it needed to be rounded to the next higher number

    double firstDist = abs(value - tempValue);  //finding distance from value to lower rounding
    double secondDist = abs(value - higherTempValue); //distance from value to higher rounding

    tempValue = (firstDist < secondDist) ? tempValue : higherTempValue; //returns value w smaller distance, i.e. the closest one
    value = tempValue / multiplier; //dividing to get real decimal

    return value;
}

void BankAccount::calcInt()
{
    double dailyIntRate = intRate / 365; //maybe change in future to account for leap years
    double dailyInt = dailyIntRate * balance;
    balance = roundNum(balance + dailyInt, 2); //private member function to round to a given amount of decimals
}

//Setter and Getter functions
void BankAccount::setActNum(string num)
{
    accountNum = num;
}

string BankAccount::getActNum()
{
    return accountNum;
}

void BankAccount::setBal(double bal)
{
    balance = roundNum(bal, 2);
}

double BankAccount::getBal()
{
    return balance;
}

#endif
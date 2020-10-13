/*
Group Members: Nathan Obert M03134502, Keegan Maynard 
*/
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

class BankAccount
{
private:
    string accountNum;
    double balance;
    double intRate;
    double serCharge;


public:
    BankAccount(){}
    BankAccount(string actNum, double bal, double rate);
    virtual string deposit(double amount) = 0;
    virtual string withdraw(double amount) = 0;
    void calcInt();
    void performSerCharge();
    virtual void closeAcc() = 0;
    static double roundNum(double value, int decimal); //used to help validate user input for depoit and withdraw, hence static

    //setter and getter functs, for derived class use
    void setActNum(string num);
    string getActNum();
    void setBal(double bal);
    double getBal();
    void setRate(double rate);
    double getRate();
    void setSerCharge(double charge);
    static string displayNum(double input);

    static string CURRENT_ACCT_NUM; //global variable for acct num
    static time_t LAST_INT_CALCULATION;
    static void incrementActNum(string lastActNum);
};
string BankAccount::CURRENT_ACCT_NUM = "00001"; //initial value, means there can be up to 99999 distinct accounts
time_t BankAccount::LAST_INT_CALCULATION; //in implementation, this will always be some day at midnight

void BankAccount::performSerCharge()
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
    double dailyIntRate = intRate / 365;
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

void BankAccount::setRate(double rate)
{
    try
    {
        if ( (rate > 10.00) || (rate < 0.10) ) //these are specifically for the sav account, but there's no reason to also not restrict on checking acct
        {
            throw 1;
        }
        else
        {
            intRate = rate;
        }
    }
    catch (int a)
    {
        cout << "Invalid rate\n";
    }

}

double BankAccount::getRate()
{
    return intRate;
}

void BankAccount::setSerCharge(double charge)
{
    serCharge = charge;
}

BankAccount::BankAccount(string actNum, double bal, double rate)
{
    setActNum(actNum);
    setBal(bal);
    setRate(rate);
}

//used to display a double properly in conjunction with cout
string BankAccount::displayNum(double input)
{
    string num = to_string(input);
    return num.substr(0, num.length() - 4); //cuts off the last 0000 of the double
}

//Increments the global variable for next act num
void BankAccount::incrementActNum(string lastActNum = "")
{
    int num = 0;
    if (lastActNum == "") //i.e. there are no pre-existing accounts
    {
        num = stoi(CURRENT_ACCT_NUM);
    }
    else
    {
        num = stoi( lastActNum.substr(1, string::npos) ); //used if there are currently existing accts
    }
    
    int count = 0;
    int numCopy = num; //copying value into new var
    while (numCopy >= 1)
    {
        numCopy /= 10;
        count++; //count, upon end of while loop, will represent the highest power of 10, i.e. whether in the ones, tens, hundreds, etc
    }
    
    string firstPartOfNum = "";
    while ( (firstPartOfNum.length() + count) < 5) //five digits total in act num template
    {
        firstPartOfNum += "0";
    }
    num += 1;

    CURRENT_ACCT_NUM = firstPartOfNum + to_string(num);
}
#endif
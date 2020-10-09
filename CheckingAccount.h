/*
Group Members: Nathan Obert M03134502, Keegan Maynard 
*/
#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
#include <string>
#include "BankAccount.h"
using namespace std;

class CheckingAccount : BankAccount
{
private:
    void nsfCharge();
    void setHighRisk();

public:
    void deposit();
    void withdraw();
    void closeAcc();
};
#endif
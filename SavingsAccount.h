#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H
#include <string>
#include <iostream>
#include "BankAccount.h"
using namespace std;

class SavingsAccount : public BankAccount
{
private:
	string status;
	void setStatus();
public:
	SavingsAccount(string actNum, double bal, double rate);
	void deposit(double amount);
	void withdraw(double amount);
	void closeAcc();
};

SavingsAccount::SavingsAccount(string actNum, double bal, double rate) : BankAccount(actNum, bal, rate)
{
	;
}

void SavingsAccount::deposit(double amount)
{
	try
	{
		if (amount < 0.01)
		{
			string error = "Invalid arguement: you cannot deposit a negative amount";
			throw error;
		}
		else
		{
			setBal(getBal() + amount);
		}
	}
	catch (string err)
	{
		cout << err << endl;
	}
}
#endif
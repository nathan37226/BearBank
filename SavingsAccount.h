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
	void setStatus(int option);
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

void SavingsAccount::setStatus(int option)
{
	try
	{
		string actNum = getActNum();

		switch (option)
		{
			case 1:
			{
				status = "Active";
				break;
			}
			case 2:
			{
				status = "Inactive";
				break;
			}
			case 3:
			{
				status = "Permanently Closed";
				break;
			}
			default:
			{
				string error = "Invalid arguement: setStatus expects 1 or 2, got passed the value " + to_string(option);
				throw error;
			}
		}
	}
	catch (string err)
	{
		cout << err << endl;
	}
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

void SavingsAccount::withdraw(double amount)
{
	try
	{
		if (amount < 0.01)
		{
			string error = "Invalid Arguement: cannot withdraw less than $0.00";
			throw error;
		}
	}
	catch (string err)
	{
		cout << err << endl;
	}

	double newBal = getBal() - amount;

	if (newBal < 50.0)
	{
		//charge 5 fee
		if (getBal() < 1.00)
		{
			//close
		}
		else
		{
			//set status as inactive
		}
	}
}

void SavingsAccount::closeAcc()
{
	;
}
#endif
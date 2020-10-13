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

public:
    SavingsAccount(){}
	SavingsAccount(string actNum, double bal, double rate);
	string deposit(double amount);
	string withdraw(double amount);
	void closeAcc();
    string getStatus();
    void setStatus(int option);
	void setSerCharge(double charge);
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
				string error = "Invalid arguement: setStatus expects 1, 2, or 3, got passed the value " + to_string(option);
				throw error;
			}
		}
	}
	catch (string err)
	{
		cout << err << endl;
	}
}

string SavingsAccount::getStatus()
{
    return status;
}

string SavingsAccount::deposit(double amount)
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
    string amnt = to_string(amount);
    amnt = amnt.substr(0, amnt.length() - 4); //takes off the "0000" at the end of the double
    return "You have successfully deposited $" + amnt + " into your account.";
}

string SavingsAccount::withdraw(double amount)
{
	string newStatus;
	try
	{
		if (amount < 0.01)
		{
			string error = "Invalid Arguement: cannot withdraw less than $0.01";
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
		setSerCharge(5.0);
		performSerCharge();
		
		if (getBal() < 1.00)
		{
			setStatus(3);
		}
		else
		{
			setStatus(2);
		}
	}
	if (status == "Inactive")
	{
		newStatus = "There is less than $50.00 in the account, it is now inactive. No more withdrawls can be made until there is more than $50.00 in the account" << endl;
		return newStatus;
	}
	else if (status == "Permanently Closed")
	{
		newStatus = "There is less than $1.00 in the account, it has been permanently closed. " << endl;
		return newStatus;
	}
	else 
	{
		setBal(newBal);
	}
	string amnt = to_string(amount);
	amnt = amnt.substr(0, amnt.length() - 4); //takes off the "0000" at the end of the double
	return "You have withdrawn $" + amnt + " from you account.";
}

void SavingsAccount::closeAcc()
{
	;
}
#endif
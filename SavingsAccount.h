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

	void updateStatus();

public:
    SavingsAccount(){}
	SavingsAccount(string actNum, double bal, double rate);
	string deposit(double amount);
	string withdraw(double amount);
	void closeAcc();
    string getStatus();
    void setStatus(int option);
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

void SavingsAccount::updateStatus()
{
	if (getBal() >= 50.00)
	{
		setStatus(1);
	}
}

string SavingsAccount::deposit(double amount)
{
	if (status == "Permanently Closed")
	{
		string inactive = "Error, this account has been closed and is no longer active.";
		return inactive;
	}
	else
	{
		try
		{
			if(amount < 0.01)
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
		updateStatus(); //if >= $50.00, then status is active
		return "You have successfully deposited $" + displayNum(amount) + " into your account.";
	}
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

	if (status == "Inactive")
	{
		return "No withdrawls can be made until this account has a balance of at least $50.00";
	}

	else
	{
		double newBal = getBal() - amount; //bal after withdraw
		if (newBal < 50.0)
		{
			setSerCharge(5.0);
			performSerCharge(); //charges the $5.00 fee for dropping below $50.00
			
			if (getBal() < 1.00)
			{
				setStatus(3); //permanently closing the acct
				setBal(newBal); //charging the bad withdraw attempt
				return "You have withdrawn $" + BankAccount::displayNum(amount) + " from you account.\nYour balance has dropped below $1.00.\nThe account has been permanently closed.";
			}
			else
			{
				setStatus(2); //setting acct as inactive
				setBal(newBal); //charging the withdraw
				return "You have withdrawn $" + BankAccount::displayNum(amount) + " from you account.\nYour balance has dropped below $50.00.\nThe account has been set to inactive.\nDeposit to resume activity.";
			}
		}
		else
		{
			setBal(newBal); //everything is fine at this point
		}
	}
	return "You have withdrawn $" + BankAccount::displayNum(amount) + " from you account.";
}

void SavingsAccount::closeAcc()
{
	;
}
#endif
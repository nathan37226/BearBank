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
	if (isOpen())
	{
		if (status == "Permanently Closed")
		{
			string inactive = "Error, this account has been closed and is no longer active.";
			return inactive;
		}
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
	else
	{
		return "The account is currently closed\n";
	}
}

string SavingsAccount::withdraw(double amount)
{
	if (isOpen()) //only if open is the acct able to withdraw
	{
		string newStatus;

		//These if statements are for redundancy, in case there is an error in OS.h with the account status
		if (status == "Inactive")
		{
			newStatus = "There is less than $50.00 in the account, it is now inactive. No more withdrawls can be made until there is more than $50.00 in the account\n";
			return newStatus;		//returns status of the account, discards the withdrawl
		}
		else if (status == "Permanently Closed")
		{
			newStatus = "There is less than $1.00 in the account, it has been permanently closed.\n";
			return newStatus;		//returns status of the account, discards the withdrawl
		}
		else
		{
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

			setBal(newBal);

			return "You have withdrawn $" + BankAccount::displayNum(amount) + " from you account.";
		}
	}
	else
	{
		return "The account is currently closed\n";
	}
	
}

void SavingsAccount::closeAcc()
{
	setIsClosed(true);
}
#endif
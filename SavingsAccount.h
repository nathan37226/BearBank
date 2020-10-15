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
				throw "Invalid arguement: setStatus expects 1, 2, or 3, got passed the value " + to_string(option);
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
			return "Error, this account has been closed and is no longer active.\n";
		}
		try
		{
			if (amount < 0.01)
			{
				throw "Invalid argument: you cannot deposit a negative amount.\n";
			}
			else
			{
				setBal(getBal() + amount);

				if (getBal() > 50.00)
				{
					setStatus(1);
				}
			}
		}
		catch (string err)
		{
			cout << err << endl;
		}
		return "You have successfully deposited $" + BankAccount::displayNum(amount) + " into your account.\n";
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
		//These if statements are for redundancy, in case there is an error in OS.h with the account status
		if (status == "Inactive")
		{
			return "There is less than $50.00 in the account, it is now inactive. No more withdrawls can be made until there is more than $50.00 in the account\n";		//returns status of the account, discards the withdrawl
		}
		else if (status == "Permanently Closed")
		{
			return "There is less than $1.00 in the account, it has been permanently closed.\n";		//returns status of the account, discards the withdrawl
		}
		else //active
		{
			if (amount < 0.01)
			{
				return "You cannot withdraw less than $0.01";
			}
			else
			{
				double newBal = getBal() - amount;

				if (newBal < 0.0) //not allowed to go negative
				{
					return "There is not sufficient funds for this withdrawl.\n";
				}
				else if (newBal < 50.0)
				{
					setSerCharge(5.0);
					performSerCharge();
					setBal(newBal); //charging request

					if (getBal() < 1.00)
					{
						setStatus(3); //permanently closing
					}
					else
					{
						setStatus(2); //sets as inactive
					}
				}

				return "You have withdrawn $" + BankAccount::displayNum(amount) + " from you account.";
			}
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
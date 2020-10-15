/*
Group Members: Keegan Maynard M03114078 and Nathan Obert M03134502
*/
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
		string actNum = getActNum();		//for easier access later

		switch (option)		//set the status of the account 
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
				status = "Permanently-Closed";
				setIsClosed(true);		//close the account 
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
    return status;		//returns the status of the account: active, inactive, or permanently closed
}

string SavingsAccount::deposit(double amount)
{
	if (isOpen())		//only if the account is open will the deposit take place
	{
		try
		{
			if (amount < 0.01)		//cannot deposit $0.00 into the account
			{
				throw "Invalid argument: you cannot deposit a negative amount.\n";
			}
			else
			{
				setBal(getBal() + amount);		//set the new balance as the old balance plus the deposit

				if (getBal() > 50.00)		//if there is more than $50 in the account 
				{
					setStatus(1);		//set status as active
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
		if (status == "Permanently-Closed")			//if the account is permanently closed	
		{
			return "Error, this account has been permanently closed.\n";
		}
		else
		//if the account is currently closed
		{
			return "This account is currently closed.\n";
		}
		
	}
}

string SavingsAccount::withdraw(double amount)
{
	if (isOpen()) //only if open is the acct able to withdraw
	{
		//This if statement is for redundancy, in case there is an error in OS.h with the account status
		if (status == "Inactive")
		{
			return "There is less than $50.00 in the account, it is now inactive. No more withdrawls can be made until there is more than $50.00 in the account\n";		//returns status of the account, discards the withdrawl
		}
		else //active
		{
			if (amount < 0.01)
			{
				return "You cannot withdraw less than $0.01";
			}
			else
			{
				//only if the user withdraws more than $0.00

				double newBal = getBal() - amount;		//set the new balance as the old balance minus the amount 

				if (newBal < 0.0) //not allowed to go negative
				{
					return "There is not sufficient funds for this withdrawl.\n";
				}
				else if (newBal < 50.0)
				{
					//Only if there is less than $50.00 in the account

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
		if (status == "Permanently-Closed")
		{
			return "There is less than $1.00 in the account, it has been permanently closed.\n"; //returns status of the account, discards the withdrawl
		}
		else
		{
			return "The account is currently closed\n";
		}
		
	}
	
}

void SavingsAccount::closeAcc()
{
	setIsClosed(true);
}
#endif
/*
Group Members: Nathan Obert M03134502, Keegan Maynard 
*/
#include "OS.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;




int main()
{
    vector<Accounts> acctVect = getInfo(); //gets any info if present, otherwise returns am empty vect

    string mainInterface = "\n[1] Open an account\n[2] Login to an account\n[3] Exit bank\n";
    string accountInterface = "\n[1] Display Balance\n[2] Make a deposit\n[3] Make a withdrawl\n";
    
    if (acctVect.size() > 0)
    {
        saveInfo(acctVect); //computes initial interest and saves to .txt file. Worst case, it will exactly rewrite existing contents in .txt file
        BankAccount::incrementActNum( acctVect[acctVect.size()-1].chk.getActNum() ); //uses last acct num from .txt file to generate next num
    }
    else
    {
        BankAccount::LAST_INT_CALCULATION = midnightTimeStamp(time(0)); //since nothing in vector, no current timestamp. this initializes it to be the current day at midnight
    }
    

    while (true) //main while loop
    {
        cout << mainInterface;
        string input = "";
        int option = -1;
        getline(cin, input);

        try //validating input
        {
            if (input.length() == 1)
                option = stoi(input); //Since stoi will make "2a" become 2, ensuring the length is 1 prevents this type of invalid input, also same with negative numbers
            else
                throw 1; //just throwing any int here to be caught later
        }
        catch (...)
        {
            cout << "Invalid option!" << endl;
            continue;
        }
        
        switch (option)
        {
            case 1: //open new accounts
            {
                string chkNum = "", savNum = "";
                chkNum = "C" + BankAccount::CURRENT_ACCT_NUM;
                savNum = "S" + BankAccount::CURRENT_ACCT_NUM;
                BankAccount::incrementActNum(); //used that num, so need to prepare for next number

                cout << "Your account numbers are " << chkNum << " and " << savNum << " for your ";
                cout << "new Checking Account and Savings Account, respectively." << endl;
                cout << "Your Checking Account, " << chkNum << ", has an initial balance of $5.00 with an interest rate of 0.5%" << endl;
                cout << "Your Savings Account, " << savNum << ", has an initial balance of $50.00 with an interest rate of 1.5%" << endl;
                
                CheckingAccount newChkAcct = CheckingAccount(chkNum, 5.00, 0.5); //creating the checking acct
                SavingsAccount newSavAcct = SavingsAccount(savNum, 50.00, 1.5); //same with savings acct
                newSavAcct.setStatus(1); //making it active

                Accounts newSet; //struct object to store the two new accts
                newSet.chk = newChkAcct;
                newSet.sav = newSavAcct;
                acctVect.push_back(newSet); //adding new accts to vect

                saveInfo(acctVect); //in case of premature exit of program, info is still saved
                break;
            }

            case 2: //login to accounts
            {                
                int userOption = 0; //different input option for clarity / break main while loop condition further below
                string actNum = "";
                cout << "Enter an account number: ";
                getline(cin, actNum);

                int index = findAcctIndex(acctVect, actNum);

                if (index == -1) //acount does not exist
                {
                    cout << "Account not found!" << endl;
                }

                else //account exists, so deposit or withdraw
                {
                    cout << accountInterface; //displays options for an acct
                    getline(cin, input);

                    try //this is yet another input check
                    {
                        if (input.length() == 1) //this ensures option will never go to 3 if "3" is input, which saves while loop
                            userOption = stoi(input); //Since stoi will make "2a" become 2, ensuring the length is 1 prevents this type of invalid input, also same with negative numbers
                        else
                            throw 1; //just throwing any int here to be caught later
                    }
                    catch (...)
                    {
                        cout << "Invalid option!" << endl;
                        continue;
                    }

                    string amount = "";
                    switch (userOption)
                    {
                        case 1: //display balance
                        {
                            displayBalance(acctVect, actNum, index); //abstracted to make code more readable
                            break;
                        }
                        case 2: //making a deposit
                        {
                            userDeposit(acctVect, actNum, index); //also abstracted 
                            displayBalance(acctVect, actNum, index); //displaying balance again
                            break;
                        }
                        case 3: //making a withdrawl
                        {
                            userWithdraw(acctVect, actNum, index);  
                            displayBalance(acctVect, actNum, index);                        
                            break;
                        }
                        default: //bad option
                        {
                            cout << "Invalid Option!" << endl;
                            break;
                        }
                    }
                    saveInfo(acctVect);
                }
            }

            case 3: //Exit BearBank
            {
                saveInfo(acctVect); //send account info to be saved into the oh so safe .txt file
                break;
            }

            default: //bad option entered
            {
                cout << "Invalid option!" << endl;
                break;
            }
        }

        if (option == 3) //break condition for while loop
            break;
    }

    return 0;
}


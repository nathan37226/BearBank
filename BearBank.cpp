/*
Group Members: Nathan Obert M03134502, Keegan Maynard 
*/
#include <iostream>
#include "OS.h"
#include <string>
#include <vector>
using namespace std;

int main()
{   
    vector<Accounts> acctVect = {Accounts()}; //makes size be 1, used for increment acct Num
    acctVect = getInfo(); //gets any existing info, if present

    string mainInterface = "\n[1] Open an account\n[2] Login to an account\n[3] Exit bank\n";
    string accountInterface = "\n[1] Make a deposit\n[2] Make a withdrawl";
    BankAccount::incrementActNum( acctVect[acctVect.size()-1].chk.getActNum() );


    while (true) //main while loop
    {
        cout << mainInterface << endl;
        string input = "";
        int option = -1;
        getline(cin, input);

        try
        {
            if (input.length() == 1)
                option = stoi(input); //Since stoi will make "2a" become 2, ensuring the length is 1 prevents this type of invalid input, also same with negative numbers
            else
                throw 1; //just throwing any int here to be caught later
        }
        catch (int a)
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
                cout << "Your Savings Account, " << savNum << ", has an initial balance of $50.00 with an interst rate of 1.5%" << endl;
                
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
                cout << "Enter an account number: ";
                string actNum = "";
                getline(cin, actNum);
                int index = findAcctIndex(acctVect, actNum);

                if (index == -1) //acount does not exist
                {
                    cout << "Account not found!" << endl;
                }

                else //account exists, so deposit or withdraw
                {
                    displayBalance(acctVect, actNum, index); //displays user's balance
    
                    cout << accountInterface << endl; //displays options for an acct
                    getline(cin, input);

                    try //this is yet another input check
                    {
                        if ((input.length() == 1) && (input != "3")) //this ensures option will never go to 3 if "3" is input, which saves while loop
                            option = stoi(input); //Since stoi will make "2a" become 2, ensuring the length is 1 prevents this type of invalid input, also same with negative numbers
                        else
                            throw 1; //just throwing any int here to be caught later
                    }
                    catch (int a)
                    {
                        cout << "Invalid option!" << endl;
                        continue;
                    }

                    string amount = "";
                    switch (option)
                    {
                        case 1: //making a deposit
                        {
                            userDeposit(acctVect, actNum, index);
                            break;
                        }
                        case 2: //making a withdrawl
                        {
                            userWithdraw(acctVect, actNum, index);                          
                            break;
                        }
                        default:
                        {
                            cout << "Invalid Option!" << endl;
                            break;
                        }
                    }
                }
                displayBalance(acctVect, actNum, index); //displays user's balance after withdraw or deposit
                saveInfo(acctVect); //just in case of premature exit of program, info is still saved
            }

            case 3: //Exit BearBank
            {
                saveInfo(acctVect); //send account info to be saved into the oh so safe .txt file
                break;
            }

            default:
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

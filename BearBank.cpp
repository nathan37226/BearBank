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
    
    string mainInterface = "[1] Open an account\n[2] Login to an account\n[3] Exit bank";
    string whichAccount = "[1] Checking Account\n[2] Savings Account";
    string accountInterface = "[1] Make a deposit\n[2] Make a Withdrawl";
    incrementActNum( acctVect[acctVect.size()-1].chk.getActNum() );

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
                chkNum = "C" + CURRENT_ACCT_NUM;
                savNum = "S" + CURRENT_ACCT_NUM;
                incrementActNum(); //used that num, so need to prepare for next number
                cout << "Your account numbers are " << chkNum << " and " << savNum << " for your ";
                cout << " new Checking Account and Savings Account, respectively." << endl;
                cout << "Your Checking Account, " << chkNum << ", has an initial balance of $5.00 with an interest rate of 0.5%" << endl;
                cout << "Your Savings Account, " << savNum << ", has an initial balance of $50.00 with an interst rate of 1.5%" << endl;
                
                CheckingAccount newChkAcct = CheckingAccount(chkNum, 5.00, 0.5); //creating the checking acct
                SavingsAccount newSavAcct = SavingsAccount(savNum, 50.00, 1.5); //same with savings acct
                Accounts newSet; //struct object to store the two new accts
                newSet.chk = newChkAcct;
                newSet.sav = newSavAcct;
                acctVect.push_back(newSet); //adding new accts to vect
            }

            case 2: //login to accounts
            {
                ;
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

        if (option == 3)
            break;
    }



    return 0;
}

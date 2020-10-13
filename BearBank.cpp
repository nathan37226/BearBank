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
                ;
            }

            case 2: //login to accounts
            {
                ;
            }

            case 3: //Exit BearBank
            {
                ;
            }
        }

        if (option == 3)
            break;
    }



    return 0;
}

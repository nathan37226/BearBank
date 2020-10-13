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
    cout << INITIAL_ACCT_NUM << endl;

    vector<Accounts> acctVect = {Accounts()}; //makes size be 1, used for increment acct Num
    acctVect = getInfo(); //gets any existing info, if present
    
    string mainInterface = "[1] Open an account\n[2] Login to an account\n[3] Exit bank";
    string whichAccount = "[1] Checking Account\n[2] Savings Account";
    string accountInterface = "[1] Make a deposit\n[2] Make a Withdrawl";
    incrementActNum( acctVect[acctVect.size()-1].chk.getActNum() );

    cout << INITIAL_ACCT_NUM << endl;

    /*while (true) //main while loop
    {
        cout << mainInterface << endl;

    }*/



    return 0;
}

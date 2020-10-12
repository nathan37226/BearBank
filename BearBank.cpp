/*
Group Members: Nathan Obert M03134502, Keegan Maynard 
*/
#include <iostream>
#include "OS.h"
#include <string>
#include <vector>



int main()
{   
    vector<Accounts> acctVect = {};
    acctVect = getInfo();
    string message;
    cout << acctVect[0].chk.getBal() << endl;
    acctVect[0].chk.deposit(420.00);
    cout << message << endl;
    cout << to_string(acctVect[0].chk.getBal()) << endl;
    return 0;
}

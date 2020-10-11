/*
Group Members: Nathan Obert M03134502, Keegan Maynard 
*/
#include <iostream>
#include "CheckingAccount.h"
#include "OS.h"
#include <string>
#include <vector>



int main()
{
    CheckingAccount acc1 = CheckingAccount("C001", 50.05, 1.02);
    Accounts actSet1;
    actSet1.chk = acc1;
    CheckingAccount acc2 = CheckingAccount("C002", 100.05, 2.00);
    Accounts actSet2;
    actSet2.chk = acc2;
    CheckingAccount acc3 = CheckingAccount("C003", 200.99, 1.95);
    Accounts actSet3;
    actSet3.chk = acc3;

    vector<Accounts> acctVect {actSet1, actSet2, actSet3};

    saveInfo(acctVect);

    return 0;
}

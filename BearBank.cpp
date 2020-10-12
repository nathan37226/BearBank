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

    /*CheckingAccount acc1 = CheckingAccount("C001", 50.05, 1.02);
    Accounts actSet1;
    actSet1.chk = acc1;
    CheckingAccount acc2 = CheckingAccount("C002", 100.05, 2.00);
    Accounts actSet2;
    actSet2.chk = acc2;
    CheckingAccount acc3 = CheckingAccount("C003", 200.99, 1.95);
    Accounts actSet3;
    actSet3.chk = acc3;*/

    for (int i = 0; i < acctVect.size(); i++)
    {
        cout << acctVect[i].chk.getActNum() << " " << acctVect[i].chk.getBal() << " " << acctVect[i].chk.getRate() << endl;
        cout << acctVect[i].sav.getActNum() << " " << acctVect[i].sav.getStatus() << " " << acctVect[i].sav.getRate() << endl;
    }

    //saveInfo(acctVect);

    return 0;
}

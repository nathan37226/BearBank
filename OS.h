#ifndef OS_H
#define OS_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "CheckingAccount.h"
//#include "SavingsAccount.h"
using namespace std;

struct Accounts
{
    CheckingAccount chk;
    //SavingsAccount sav;
};

string getAccountInfo(Accounts accts)
{
    string chkInfo = "";
    chkInfo = accts.chk.getActNum() + " " + to_string( accts.chk.getBal() ) + " " + to_string( accts.chk.getRate() );
    
    return chkInfo;

}

void saveInfo(vector<Accounts> acctVect)
{
    ofstream outFile;
    outFile.open("TotallyNotBankInfo.txt");

    for (int i=0; i < acctVect.size(); i++)
    {
        outFile << getAccountInfo(acctVect[i]) << endl;
    }

    outFile.close();
}

#endif
#ifndef OS_H
#define OS_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "CheckingAccount.h"
#include "SavingsAccount.h"
using namespace std;

struct Accounts
{
    CheckingAccount chk;
    SavingsAccount sav;
};

string displayNum(double input);
string getAccountInfo(Accounts accts);
bool validateInput(string inputNum);
int findAcctIndex(vector<Accounts> vect, string actNum);
void incrementActNum(string lastActNum);
vector<Accounts> getInfo();
void saveInfo(vector<Accounts> acctVect);
CheckingAccount createChkFromInfo(string info);
SavingsAccount createSavFromInfo(string info);

string INITIAL_ACCT_NUM = "00001"; //global variable for acct num

string displayNum(double input)
{
    string num = to_string(input);
    return num.substr(0, num.length() - 4); //cuts off the last 0000 of the double
}

string getAccountInfo(Accounts accts)
{
    string chkInfo = "", savInfo;
    chkInfo = accts.chk.getActNum() + " " + to_string( accts.chk.getBal() ) + " " + to_string( accts.chk.getRate() );

    if (accts.sav.getStatus() == "Permanently Closed")
    {
        savInfo = "CLOSED SAVINGS ACCOUNT";
    }
    else
    {
        savInfo = accts.sav.getActNum() + " " + to_string( accts.sav.getBal() ) + " " + to_string( accts.chk.getRate() );
        savInfo += " " + accts.sav.getStatus();
    }
    

    return chkInfo + "\n" + savInfo;
}

bool validateInput(string inputNum)
{
    double num = stod(inputNum);
    if (num < 0.01) //cannot withdraw or deposit less than a cent
    {
        return false;
    }
    else
    {
        if (num != BankAccount::roundNum(num, 2)) //e.g. depositing 10.056 isn't the same as 10.05
        {
            return false;
        }
        else //if a rounded double to 2 decimals is the same as the input, then the number is valid!
        {
            return true;
        }
    }    
}

int findAcctIndex(vector<Accounts> vect, string actNum)
{
    for (int i = 0; i < vect.size(); i++)
    {
        if ( (actNum == vect[i].chk.getActNum()) || (actNum == vect[i].sav.getActNum()) )
        {
            return i;
        }
    }
    return -1; //only hit if never found act num
}

void incrementActNum(string lastActNum = "")
{
    int num = 0;
    if (lastActNum == "")
    {
        num = stoi(INITIAL_ACCT_NUM);
    }
    else
    {
        num = stoi( lastActNum.substr(1, string::npos) ); //used if there are currently existing accts
    }
    
    int count = 0;
    int numCopy = num; //copying value into new var
    while (numCopy >= 1)
    {
        numCopy /= 10;
        count++; //count, upon end of while loop, will represent the highest power of 10, i.e. whether in the ones, tens, hundreds, etc
    }
    
    string firstPartOfNum = "";
    while ( (firstPartOfNum.length() + count) < 5) //five digits total in act num template
    {
        firstPartOfNum += "0";
    }
    num += 1;

    INITIAL_ACCT_NUM = firstPartOfNum + to_string(num);
}

vector<Accounts> getInfo()
{
    vector<Accounts> acctVect = {};
    ifstream inputFile;
    inputFile.open("TotallyNotBankInfo.txt");

    if (!inputFile) //i.e. no bank info to read
    {
        return acctVect;
    }

    else  //i.e. there is bank info saved
    {
        string chkLine = "", savLine = "";

        while (getline(inputFile, chkLine))
        {
            getline(inputFile, savLine);
            Accounts accSet; //now need to copy data froms strings into struct attributes
            CheckingAccount check = createChkFromInfo(chkLine); //creates checking act from line
            SavingsAccount saving = createSavFromInfo(savLine); //same with next line

            accSet.chk = check; //adding new accts to struct
            accSet.sav = saving;

            acctVect.push_back(accSet); //adding the struct object to the vector
        }

        inputFile.close(); //done reading, so this can be closed
        return acctVect;
    }
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

CheckingAccount createChkFromInfo(string info)
{
    string actNum = info.substr(0, info.find(" ")); //slicing out act Num
    info = info.substr(info.find(" ") + 1, string::npos);
    double bal = stod( info.substr(0, info.find(" ")) ); //getting balance as a double
    info = info.substr(info.find(" ") + 1, string::npos);
    double rate = stod( info ); //getting rate as a double

    CheckingAccount acct = CheckingAccount(actNum, bal, rate); //creating account with sliced info

    if (actNum.substr(actNum.length() - 1, string::npos) == "*") //seeing if High Risk or not
    {
        acct.setRisk(2); //ensures the priv member 'flag' is properly set
    }

    return acct; //return newly minted checking account object
}

SavingsAccount createSavFromInfo(string info)
{
    if (info == "CLOSED SAVINGS ACCOUNT")
    {
        SavingsAccount acct = SavingsAccount();
        acct.setStatus(3);
        return acct;
    }
    else
    {    
        string actNum = info.substr(0, info.find(" ")); //slicing out act Num
        info = info.substr(info.find(" ") + 1, string::npos); //shorting string
        double bal = stod( info.substr(0, info.find(" ")) ); //getting balance as a double
        info = info.substr(info.find(" ") + 1, string::npos);
        double rate = stod( info.substr(0, info.find(" ")) ); //getting rate as a double
        info = info.substr(info.find(" ") + 1, string::npos);
        //info is now just the status of the act
        SavingsAccount acct = SavingsAccount(actNum, bal, rate); //creating return object

        if (info == "Active")
        {
            acct.setStatus(1); //changing status member to match
        }
        else
        {
            acct.setStatus(2);
        }
        return acct;
    }
}

#endif
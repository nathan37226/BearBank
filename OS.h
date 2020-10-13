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

inline string displayNum(double input);
inline void displayBalance(vector<Accounts> acctVect, string actNum, int index);
inline vector<Accounts> userDeposit(vector<Accounts> acctVect, string actNum, int index, double amount);
inline vector<Accounts> userWithdraw(vector<Accounts> acctVect, string actNum, int index);
inline string getAccountInfo(Accounts accts);
inline bool validateInput(string inputNum);
inline int findAcctIndex(vector<Accounts> vect, string actNum);
inline void incrementActNum(string lastActNum);
inline vector<Accounts> getInfo();
inline void saveInfo(vector<Accounts> acctVect);
inline CheckingAccount createChkFromInfo(string info);
inline SavingsAccount createSavFromInfo(string info);

string CURRENT_ACCT_NUM = "00001"; //global variable for acct num, means there can be up to 100000 distinct accounts

//used to display a double properly in conjunction with cout
inline string displayNum(double input)
{
    string num = to_string(input);
    return num.substr(0, num.length() - 4); //cuts off the last 0000 of the double
}

//displays user's balance
inline void displayBalance(vector<Accounts> acctVect, string actNum, int index)
{
    if (actNum.substr(0, 1) == "C")
    {
        cout << "Your account has a balance of: $" + displayNum(acctVect[index].chk.getBal()) << endl;
    }
    else
    {
        cout << "Your account has a balance of: $" + displayNum(acctVect[index].sav.getBal()) << endl;
    }
}

//simulating a user making a deposit
inline vector<Accounts> userDeposit(vector<Accounts> acctVect, string actNum, int index, double amount)
{
    string message = "";
    if (actNum.substr(0, 1) == "C") //into checking
    {
        message = acctVect[index].chk.deposit(amount);
        cout << message << endl;
    }
    else //into saving
    {
        message = acctVect[index].sav.deposit(amount);
        cout << message << endl;
    }
    return acctVect;
}

//simulating a user making a withdrawl
inline vector<Accounts> userWithdraw(vector<Accounts> acctVect, string actNum, int index)
{
    //FIND IF STATUS WILL ALLOW WITHDRAW!!!
    string amount = "";
    cout << "Enter an amount to withdraw: ";
    getline(cin, amount);
    if ( !validateInput(amount) )
    {
        cout << "Invalid number entered!" << endl;
    }

    string message = "";
    if (actNum.substr(0, 1) == "C") //from checking acct
    {
        message = acctVect[index].chk.withdraw(amount);
        cout << message << endl;
    }
    else //from saving acct
    {
        message = acctVect[index].sav.withdraw(amount);
        cout << message << endl;
    }
    return acctVect;
}

//returns all info about a set of accounts as a string
inline string getAccountInfo(Accounts accts)
{
    string chkInfo = "", savInfo = "";
    chkInfo = accts.chk.getActNum() + " " + to_string( accts.chk.getBal() ) + " " + to_string( accts.chk.getRate() ); //all relevant info for a checking acct

    if (accts.sav.getStatus() == "Permanently Closed")
    {
        savInfo = "CLOSED SAVINGS ACCOUNT"; //will never have more info
    }
    else
    {
        savInfo = accts.sav.getActNum() + " " + to_string( accts.sav.getBal() ) + " " + to_string( accts.sav.getRate() ); 
        savInfo += " " + accts.sav.getStatus(); //all relevant savings account info
    }
    
    return (chkInfo + "\n" + savInfo); //returns a string that will cover two lines in a text file
}

//determines if a user's input is valid for depositing or withdrawing
inline bool validateInput(string inputNum)
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

//Search act vector using an actNum, find index of account set
inline int findAcctIndex(vector<Accounts> vect, string actNum)
{
    for (int i = 0; i < vect.size(); i++)
    {
        string chk = vect[i].chk.getActNum();
        if (chk.substr(chk.length() - 1, string::npos) == "*")
        {
            chk = chk.substr(0, chk.length()-1); //removing the high risk marker
        }
        if ( (actNum == chk) || (actNum == vect[i].sav.getActNum()) ) //used OR since actNum can start with C or S
        {
            return i;
        }
    }
    return -1; //only hit if never found act num
}

//Increments the global variable for next act num
inline void incrementActNum(string lastActNum = "")
{
    int num = 0;
    if (lastActNum == "") //i.e. there are no pre-existing accounts
    {
        num = stoi(CURRENT_ACCT_NUM);
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

    CURRENT_ACCT_NUM = firstPartOfNum + to_string(num);
}

//Reads a .txt file for pre-existing account info
inline vector<Accounts> getInfo()
{
    vector<Accounts> acctVect = {}; //initial vector to be returned, no elements
    ifstream inputFile;
    inputFile.open("TotallyNotBankInfo.txt"); //our safe and trustworthy database of account info

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

        inputFile.close(); //done reading, so file can be closed
        return acctVect; //return our newly minted vector with acct info
    }
}

//Writes account info into a totally safe .txt file
inline void saveInfo(vector<Accounts> acctVect)
{
    ofstream outFile;
    outFile.open("TotallyNotBankInfo.txt"); //this will rewrite our 100% secure database entirely, i.e. open with trunc

    for (int i=0; i < acctVect.size(); i++)
    {
        outFile << getAccountInfo(acctVect[i]) << endl; //writes two lines of the txt file at a time, one for chk info and the other for sav info
    }
    outFile.close(); //done writing, so close the file
}

//Used to help create CheckingAccount objects from a line of text
inline CheckingAccount createChkFromInfo(string info)
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

//Same as above but with a SavingsAccount object
inline SavingsAccount createSavFromInfo(string info)
{
    if (info == "CLOSED SAVINGS ACCOUNT")
    {
        SavingsAccount acct = SavingsAccount();
        acct.setStatus(3);
        return acct; //the permanently closed status will prevent all future editing, so this should never again be changed
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
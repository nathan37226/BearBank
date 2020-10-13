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

inline void displayBalance(vector<Accounts> &acctVect, const string &actNum, const int &index);
inline void userDeposit(vector<Accounts> &acctVect, string &actNum, const int &index);
inline void userWithdraw(vector<Accounts> &acctVect, string &actNum, const int &index);
inline string getAccountInfo(Accounts &accts);
inline bool validateInput(const string &inputNum);
inline int findAcctIndex(vector<Accounts> vect, const string &actNum);
inline vector<Accounts> getInfo();
inline void saveInfo(vector<Accounts> &acctVect);
inline CheckingAccount createChkFromInfo(string info);
inline SavingsAccount createSavFromInfo(string info);
inline int daysElapsed(time_t &previousTime);
inline void computeInterest(vector<Accounts> &acctVect, time_t previousTime);
inline time_t midnightTimeStamp();



//displays user's balance
inline void displayBalance(vector<Accounts> &acctVect, const string &actNum, const int &index)
{
    if (actNum.substr(0, 1) == "C")
    {
        cout << "Your account has a balance of: $" + BankAccount::displayNum(acctVect[index].chk.getBal()) << endl;
    }
    else
    {
        cout << "Your account has a balance of: $" + BankAccount::displayNum(acctVect[index].sav.getBal()) << endl;
    }
}

//simulating a user making a deposit
inline void userDeposit(vector<Accounts> &acctVect, string &actNum, const int &index)
{
    string amount = "";
    cout << "Enter an amount to deposit: ";
    getline(cin, amount);
    if ( !validateInput(amount) )
    {
        cout << "Invalid number entered!" << endl;
    }
    else
    {
        string message = "";
        if (actNum.substr(0, 1) == "C") //into checking
        {
            message = acctVect[index].chk.deposit( stod(amount));
            cout << message << endl;
        }
        else //into saving
        {
            message = acctVect[index].sav.deposit( stod(amount) );
            cout << message << endl;
        }
    }
}

//simulating a user making a withdrawl
inline void userWithdraw(vector<Accounts> &acctVect, string &actNum, const int &index)
{
    string status = acctVect[index].sav.getStatus();

    if ( (actNum.substr(0, 1) == "S") && (status == "Inactive") )
    {
        cout << "Your savings account is inactive!\nIts balance must reach 50.00 before withdrawing is enabled." << endl;
    }
    else //either checking or an active saving
    {
        string amount = "";
        cout << "Enter an amount to withdraw: ";
        getline(cin, amount);
        if ( !validateInput(amount) )
        {
            cout << "Invalid number entered!" << endl;
        }
        else //a proper number entered
        {
            string message = "";
            if (actNum.substr(0, 1) == "C") //for checking
            {
                message = acctVect[index].chk.withdraw( stod(amount) );
                cout << message << endl;
            }
            else //for active saving
            {
                message = acctVect[index].sav.withdraw( stod(amount) );
                cout << message << endl;
            }
        }
    }
}

//returns all info about a set of accounts as a string
inline string getAccountInfo(Accounts &accts)
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
inline bool validateInput(const string &inputNum)
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
inline int findAcctIndex(vector<Accounts> vect, const string &actNum)
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

//Reads a .txt file for pre-existing account info
inline vector<Accounts> getInfo()
{
    vector<Accounts> acctVect; //initial vector to be returned, no elements
    ifstream inputFile;
    inputFile.open("TotallyNotBankInfo.txt"); //our safe and trustworthy database of account info

    if (!inputFile) //i.e. no bank info to read
    {
        return acctVect;
    }

    else  //i.e. there is bank info saved
    {
        string chkLine = "", savLine = "", lastIntTime = "";
        getline(inputFile, lastIntTime);
        BankAccount::LAST_INT_CALCULATION = stoi(lastIntTime.substr( lastIntTime.find(" ") + 1, string::npos) ); //converts the unix time saved inside .txt file to an int

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
inline void saveInfo(vector<Accounts> &acctVect)
{
    computeInterest(acctVect, time(0)); //when info is saved, need to make sure interest is up to date

    ofstream outFile;
    outFile.open("TotallyNotBankInfo.txt"); //this will rewrite our 100% secure database entirely, i.e. open with trunc

    outFile << "Timestamp: " << BankAccount::LAST_INT_CALCULATION << endl;

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

//finding time elapsed since last interest application
inline int daysElapsed(time_t &previousTime)
{
    time_t currentTime = time(0);
    long int secondsElapsed = (currentTime - previousTime);

    int days = secondsElapsed / 86400; //86400 seconds in a day, and the int type of day will round like a floor function;
    return days;
}

//tail-recursive function to return unix timestamp of current time at midnight, used for timestamp on .txt file
inline time_t midnightTimeStamp(time_t curTime)
{
    if (curTime <= 86400)
    {
        return (time(0) - curTime); //returns how many seconds have elapsed in the current day
    }
    else
    {  
        return midnightTimeStamp(curTime-86400); //subtracts one day off
    }
}

//takes how many days have passed since last computation of interest and performs daily int caluclations
inline void computeInterest(vector<Accounts> &acctVect, time_t previousTime)
{
    int daysPassed = daysElapsed(previousTime);
    if (daysPassed > 0) //only ever calculate interest if at least 1 day has elapsed
    {
        for (int day = 0; day < daysPassed; day++) //for each day that interest needs to be accrewed
        {
            for (int index = 0; index < acctVect.size(); index++) //for each set of accounts in the vector
            {
                acctVect[index].chk.calcInt(); //adds daily interst onto balance
                acctVect[index].sav.calcInt();
            }
        }
        BankAccount::LAST_INT_CALCULATION = midnightTimeStamp(time(0)); //updates time to midnight of current day
    }
}
#endif
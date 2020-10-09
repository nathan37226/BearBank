/*
Group Members: Nathan Obert M03134502, Keegan Maynard 
*/
#include <iostream>
#include "CheckingAccount.h"
#include <string>

int main()
{
    CheckingAccount chk = CheckingAccount("C0001", 50.00, 2.00);
    chk.deposit(10000.00);
    return 0;
}

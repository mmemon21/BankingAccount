/*
 * Title: Customer.cpp
 * Abstract: This is the main class file for Customer.h and driver.cpp
 * Author: Mustafa Memon
 * ID: 9782
 * Date: 04/15/2019
 */

#include <iostream>
#include <string>
#include "Customer.h"

void Customer::removeType(int type){
    if (type == 1){
        accountNum1 = "xxxx";
        checking = false;
        balance1 = 0;
    }
    else if(type == 2){
        accountNum2 = "xxxx";
        saving = false;
        balance2 = 0;
    }
}

void Customer::yesChecking(){
    checking = true;
}

void Customer::yesSaving(){
    saving = true;
}

void Customer::minusBalance(double amount, int type1){
    if(type1 == 1){
        balance1 -= amount;
    }
    else if(type1 == 2){
        balance2 -= amount;
    }
}

void Customer::addBalance(double amount, int type2){
    if(type2 == 1){
        balance1 += amount;
    }
    else if(type2 == 2){
        balance2 += amount;
    }
}

string Customer::getfName(){
    return fName;
}

string Customer::getlName(){
    return lName;
}

string Customer::getSSN(){
    return SSN;
}

string Customer::getAccNum1(){
    return accountNum1;
}

string Customer::getAccNum2(){
    return accountNum2;
}

bool Customer::isChecking(){
    return checking;
}

bool Customer::isSaving(){
    return saving;
}

double Customer::getBalance(int type){
    if(type == 1){
        return balance1;
    }
    if(type ==2){
        return balance2;
    }
}

void Customer::setBalance(int type, double bal){
    if(type == 1){
        balance1 = bal;
    }
    if(type ==2){
        balance2 = bal;
    }
}

void Customer::setAccount(string first, string last, string ssNum, string accNum, int tp, double bal){
     fName = first; lName = last; SSN = ssNum; 
     checking = false;
     saving = false;
     if (tp == 1){
        accountNum1 = accNum;
        balance1 = bal;
        checking = true;
     }
     else if(tp == 2){
         accountNum2 = accNum;
         balance2 = bal;
         saving = true;
     }
     
}




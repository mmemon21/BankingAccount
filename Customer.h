/*
 * Title: Customer.h
 * Abstract: This is the interface class file for Customer.cpp and driver.cpp
 * Author: Mustafa Memon
 * ID: 9782
 * Date: 04/15/2019
 */
 
#include <string>
using namespace std;


class Customer{
    public:
    string getfName();
    string getlName();
    string getSSN();
    string getAccNum1();
    string getAccNum2();
    bool isSaving();
    void yesSaving();
    bool isChecking();
    void yesChecking();
    double getBalance(int type);
    void setBalance(int type, double bal);
    void minusBalance(double amount, int type1);
    void addBalance(double amount, int type2);
    void setAccount(string first, string last, string ssNum, string accNum, int tp, double bal);
    void removeType(int type);
    
    
    private:
    string fName, lName, SSN, accountNum1, accountNum2;
    bool checking, saving;
    double balance1, balance2;
};
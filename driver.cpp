/*
 * Title: driver.cpp
 * Abstract: A driver program for a Banking Software with link to the class Customer.
 *           Also an implementation file for Customer.h and Customer.cpp
 * Author: Mustafa Memon
 * ID: 9782
 * Date: 04/15/2019
 */

#include <iostream>
#include <string>
#include <fstream>
#include "Customer.h"
using namespace std;

int accountsMade = 0;
int numCustomers = 0;
const int maxCustomers = 20;

void readFile(Customer * ptr[]);
void closeAcc(Customer * ptr[]);
void customerInfo(Customer * ptr[]);
void bankInfo(Customer * ptr[]);
void transfer(Customer * ptr[]);
void customerList(Customer * ptr[]);
void printMenu();
// void display(Customer * ptr[]);

int main()
{
    // Declare an array of Account pointers.
    // The array can hold up to five Account objects.
    Customer *arrayPtr[maxCustomers];

    // Don't forget to initialize the pointers with nullptr.
    for (int i=0; i < maxCustomers; i++)
    {
        arrayPtr[i] = nullptr;
    }
    cout << "Welcome to CSUMB Bank" ;
    
    printMenu();
    int option;
    cin >> option;
    
    while(option != 7)
    {
        if(option == 1)  // Read customer data file
        {
            readFile(arrayPtr);
        }
        
        if(option == 2) // Close an account
        {
            closeAcc(arrayPtr);
        }
        
        if(option == 3) // Customer info
        {
            customerInfo(arrayPtr);
        }
        
        if(option == 4) // bank info
        {
            bankInfo(arrayPtr);
        }
        
        if(option == 5) // Transfer money
        {
           transfer(arrayPtr); 
        }
        
        if(option == 6) // Customer List
        {
            customerList(arrayPtr);
        }
        
        printMenu();
        cin >> option;
    }

    cout << "Bye" << endl;
    return 0;
}


void printMenu()
{
  cout << endl << endl;
  cout << "Select your choice:" << endl;
  cout << "     1. Read customer data file" << endl;
  cout << "     2. Close an account" << endl;
  cout << "     3. Customer Info" << endl;
  cout << "     4. Bank Info" << endl;
  cout << "     5. Transfer Money" << endl;
  cout << "     6. Customer List" << endl;
  cout << "     7. Exit" << endl;
  
}

// definition of transfer
void transfer(Customer * ptr[]){
    string fromAcc, toAcc;
    double amount;
    
    cout << "Source Account: ";
    cin >> fromAcc;
    
    cout << "Destination Account: ";
    cin >> toAcc;
    
    cout << "Money Amount: ";
    cin >> amount;
    
    
    int fromIndex = 0, toIndex = 0;
    bool found1 = false, found2 = false;
    int tp1, tp2;
    
    for(int i = 0; i < accountsMade; i++){
        if(ptr[i] == nullptr){
            continue;
        }
        
        // use accNum to see if its equal to acc1 or acc2?
        
        if((ptr[i]->getAccNum1()) == fromAcc){
            tp1 = 1;
            found1 = true;
            ptr[i]->minusBalance(amount, tp1);
        }
        else if((ptr[i]->getAccNum2()) == fromAcc){
            tp1 = 2;
            fromIndex = i;
            found1 = true;
            ptr[i]->minusBalance(amount, tp1);
        }
        if((ptr[i]->getAccNum1()) == toAcc){
            tp2 = 1;
            toIndex = i;
            found2 = true;
            ptr[toIndex]->addBalance(amount, tp2);
        }
        else if((ptr[i]->getAccNum2()) == toAcc){
            tp2 = 2;
            toIndex = i;
            found2 = true;
            ptr[toIndex]->addBalance(amount, tp2);
        }
        if(found1 && found2){
            
            if((ptr[fromIndex]->getfName() != ptr[toIndex]->getfName()) || (ptr[fromIndex]->getlName() != ptr[toIndex]->getlName())){
                ptr[fromIndex]->minusBalance(5, tp1);
                
            }
            
            cout << "Transfer Succeed." << endl;
            cout << "New Balance" << endl;
            cout.precision(5);
            cout << "   " << ptr[fromIndex]->getAccNum1() << ": $" << fixed << ptr[fromIndex]->getBalance(tp1) << endl;
            cout << "   " << ptr[toIndex]->getAccNum1() << ": $" << fixed << ptr[toIndex]->getBalance(tp2) << endl;
            
            
            break;
        }
    }
    
    
    if(!found1 && !found2){
        cout << "Transfer Fail – Incorrect account number" << endl;
        return;
    }
    
    
    cout << endl;
    
}    




// definition of bankInfo
void bankInfo(Customer * ptr[]){ 
    cout << "Number of Accounts: " << accountsMade << endl;
    for (int i = 0; i < accountsMade; i++){
        if(ptr[i] == nullptr){
            continue;
        }
        
        if(ptr[i]->isChecking()){
            cout.precision(2);
            cout << "   " << ptr[i]->getAccNum1() << ": $" << fixed << 
            ptr[i]->getBalance(1) << " (checking)" << endl;
        }
        
        if(ptr[i]->isSaving()){
            cout.precision(2);
            cout << "   " << ptr[i]->getAccNum2() << ": $" << fixed << 
            ptr[i]->getBalance(2) << " (saving)" << endl;
        }
    }
    
    cout << endl << "Number of Customers: " << numCustomers << endl;
    
    for(int i = 0; i < accountsMade; i++){
        if(ptr[i] == nullptr){
            continue;
        }
        cout << "   " << ptr[i]->getfName() << " " << ptr[i]->getlName() << ": "
             << "   " << ptr[i]->getSSN() << " - " ;
        
        if(ptr[i]->isChecking()){
            cout.precision(2);
            cout << ptr[i]->getAccNum1() << "($" << fixed << ptr[i]->getBalance(1) << ")";
        }
        
        if(ptr[i]->isChecking()){
            cout.precision(2);
            cout << ", " << ptr[i]->getAccNum2() << "($" << fixed << ptr[i]->getBalance(2) << ")";
        }
        cout << endl;
    }
       cout << endl;
    double total = 0;
    for(int i = 0; i < accountsMade; i++){
        if(ptr[i] == nullptr){
            continue;
        }
        total += ptr[i]->getBalance(1);
        total += ptr[i]->getBalance(2);
    }
     cout.precision(2);
     cout << "Total Balance: $" << fixed <<  total;
    cout << endl;
    
}

// definition of customerInfo
void customerInfo(Customer * ptr[]){
    int selection;
    cout << "SSN(1)/Last Name(2)/Account Number(3): ";
    cin >> selection;
    
    if(selection == 1){ // SSN
        string ssNum;
        cout << "Enter SSN: ";
        cin >> ssNum;
        
        for(int i = 0; i < accountsMade; i++){
            if(ptr[i] == nullptr){
                continue;
            }
        
            if((ptr[i]->getSSN()) == ssNum){
                cout << "   Name: " << ptr[i]->getfName() << " " << ptr[i]->getlName() << endl;
                
                if(ptr[i]->isChecking()){
                    cout << "   Account Number: " << ptr[i]->getAccNum1() << endl;
                    cout << "   Account Type: Checking"  << endl;
                    cout.precision(2);
                    cout << "   Balance: $" << fixed << ptr[i]->getBalance(1) << endl;
                    return;
                }
        
                if(ptr[i]->isSaving()){
                    cout << "   Account Number: " << ptr[i]->getAccNum2() << endl;
                    cout << "   Account Type: Saving"  << endl;
                    cout.precision(2);
                    cout << "   Balance: $" << fixed << ptr[i]->getBalance(2) << endl;
                    return;
                }
                
                 i++;
            }
            cout << endl;
            if(i == accountsMade){return;}
        }
       
      cout << "No Customer with the SSN." << endl << endl;
      return;
    }
    else if(selection == 2){ //Last name
         string last;
         cout << "Enter a last name: ";
        cin >> last;
        
        int i = 0; 
        while(i < accountsMade){
            if((ptr[i]->getlName()) == last){
                cout << "   Name: " << ptr[i]->getfName() << " " << ptr[i]->getlName() << endl;
                
                if(ptr[i]->isChecking()){
                    cout << "   Account Number: " << ptr[i]->getAccNum1() << endl;
                    cout << "   Account Type: Checking"  << endl;
                    cout.precision(2);
                    cout << "Balance: $" << fixed << ptr[i]->getBalance(1) << endl;
                }
        
                if(ptr[i]->isSaving()){
                    cout << "   Account Number: " << ptr[i]->getAccNum2() << endl;
                    cout << "   Account Type: Saving"  << endl;
                    cout.precision(2);
                    cout << "Balance: $" << fixed << ptr[i]->getBalance(2) << endl;
                }
                 i++;
            }
            if(i == accountsMade){return;}
        }
       
      cout << "No Customer with the last name." << endl << endl;
      return;
    }
    else if(selection == 3){ //Acc num
        string accNum;
         cout << "Enter account number: ";
        cin >> accNum;
        
        int i = 0; 
        while(i < accountsMade){
            if((ptr[i]->getAccNum1()) == accNum || ptr[i]->getAccNum2() == accNum){
                
                cout << "   Name: " << ptr[i]->getfName() << " " << ptr[i]->getlName() << endl;
               
                if(ptr[i]->isChecking()){
                    cout << "   Account Number: " << ptr[i]->getAccNum1() << endl;
                    cout << "   Account Type: Checking"  << endl;
                    cout.precision(2);
                    cout << "Balance: $" << fixed << ptr[i]->getBalance(1) << endl;
                }
        
                if(ptr[i]->isSaving()){
                    cout << "   Account Number: " << ptr[i]->getAccNum2() << endl;
                    cout << "   Account Type: Saving"  << endl;
                    cout.precision(2);
                    cout << "Balance: $" << fixed << ptr[i]->getBalance(2) << endl;
                }           
               
                 i++;
            }
            if(i == accountsMade){return;}
        }
       
      cout << "No Customer with the account number." << endl << endl;
      return;
    }    
}

// Definition of closeAcc
void closeAcc(Customer * ptr[]){
   string accNum;
   string ssNum;
   
   
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter Customer SSN: ";
    cin >> ssNum;
    bool found = false;
    
    for(int i = 0; i < accountsMade; i++){
        if(ptr[i] == nullptr){
            continue;
        } 
        
        if(ptr[i]->getAccNum1() == accNum && ptr[i]->getSSN() == ssNum){
            found = true;
            
            cout << "Account Closed" << endl;
            cout << "   Name: " << ptr[i]->getfName() << " " << ptr[i]-> getlName() << endl;
            cout << "   Account Number: " << ptr[i]-> getAccNum1() << endl;
            cout << "   Account Type: Checking" << endl;
            cout.precision(2);
            cout << fixed << "  Balance: $" << ptr[i]->getBalance(1);
            
            
            if(!(ptr[i]->isSaving())){
                delete ptr[i];
                numCustomers--;
            }
            else{
                ptr[i]->removeType(1);
            }
            
            
            for(int j = i; i < accountsMade; i++){
                ptr[i] = ptr[i+1];
            }
            
            accountsMade--;
            break;
        }
        if(ptr[i]->getAccNum2() == accNum && ptr[i]->getSSN() == ssNum){
            found = true;
            
            cout << "Account Closed" << endl;
            cout << "Name: " << ptr[i]->getfName() << " " << ptr[i]-> getlName() << endl;
            cout << "Account Number: " << ptr[i]-> getAccNum2() << endl;
            cout << "Account Type: Saving" << endl;
            cout.precision(2);
            cout << fixed << "Balance: $" << ptr[i]->getBalance(2);
            
            if(!(ptr[i]->isChecking())){
                delete ptr[i];
                numCustomers--;
            }
            else{
                ptr[i]->removeType(2);
            }
            
            for(int j = i; i < accountsMade; i++){
                ptr[i] = ptr[i+1];
            }
            
            accountsMade--;
            break;
        }
    }
    if (!found){
        cout << "No account with the Account number and SSN." << endl;
        return;
    }
}


// Definition of readFile
void readFile(Customer * ptr[]){
    char fileName[80];
    
    cout << "Enter file name: ";
    cin >> fileName;
    
    cout << "Read data..." << endl;
    
    ifstream input(fileName);
    
    int num;
    
    input >> num;
    
    string first, last, ssNum, accNum;
    int tp;
    double bal;
    while (num--) {
        if(accountsMade >= 20){
            cout << "Cant add new account - Account slots full" << endl;
            return;
        }
        input >> ssNum >> first >> last >> accNum >> tp >> bal;
        
        
        bool quitWhile = false;
        int x = -1;
        
        // Check duplication of the account number
        for(int j = 0; j < numCustomers; j++)
        {
            if(ptr[j] != nullptr){
                if(ptr[j]->getAccNum1() == accNum)
                    {
                        cout << "Account creation failed - Account number " <<
                        accNum << " already exists." << endl;
                        quitWhile = true;
                        break;
                    }
                    if(ptr[j]->getAccNum2() == accNum)
                    {
                        cout << "Account creation failed - Account number " <<
                        accNum << " already exists." << endl;
                        quitWhile = true;
                        break;
                    }
                }
        }
        if(quitWhile){
            continue;
        }
        
        // Check similarity of SSN
        for(int j = 0; j < accountsMade; j++)
        {
            if(ptr[j] != nullptr){
                if(ptr[j]->getfName() != first && ptr[j]->getSSN() == ssNum)
                {
                    cout << "Account Creation Failed – A customer with SSN " << ssNum <<" already exists."; 
                    quitWhile = true;
                    break;
                }
                
                if(ptr[j]->getfName() == first && ptr[j]->getSSN() == ssNum)
                {
                    x = j;
                    if(tp == 1){
                        if(ptr[j]->isChecking())
                        {
                            cout << "Account creation failed - " << ptr[j]->getfName() << " " <<
                            ptr[j]->getlName() << " cannot have two checking accounts. " << endl;
                            quitWhile = true;
                            break;
                        }
                        else{
                            ptr[j]->yesChecking();
                            ptr[j]->setBalance(1, bal);
                            quitWhile = true;
                            accountsMade++;
                            break;
                        }
                    }
                    if(tp == 2){
                        if(ptr[j]->isSaving())
                        {
                            cout << "Account creation failed - " << ptr[j]->getfName() << " " <<
                            ptr[j]->getlName() << " cannot have two saving accounts. " << endl;
                            quitWhile = true;
                            break;
                        }
                        else{
                            ptr[j]->yesChecking();
                            ptr[j]->setBalance(1, bal);
                            quitWhile = true;
                            accountsMade++;
                            break;
                        }
                    }
                
                    
                }
            }
        }
        if(quitWhile){
            continue;
        }
        
        
        if(quitWhile){
            continue;
        }
        
    
        if(x == -1){
            ptr[accountsMade+1] = new Customer;
            ptr[accountsMade+1]->setAccount(first, last, ssNum, accNum, tp, bal);
            numCustomers++;
        }
        
        accountsMade++;
    }
    
    
    input.close();
    
    cout << endl << "Done." << endl;
    
}

// Definition of customerList
void customerList(Customer * ptr[]){
    cout << "========== Customer List ==========" << endl;
    
    for(int i = 0; i <= accountsMade; i++){
        if(ptr[i] == nullptr){
            continue;
        }
        cout << "   SSN: " << ptr[i]->getSSN() << endl 
             << "   Name: " << ptr[i]->getfName() << " " << ptr[i]->getlName() << endl << endl;
    }
    cout << "===================================" << endl;
}

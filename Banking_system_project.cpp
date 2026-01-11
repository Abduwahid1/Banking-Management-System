#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Arrays to store account data (maximum 50 accounts)
    int accountNumber[50];
    string accountHolderName[50];
    string accountType[50];
    double balance[50];
    int totalAccounts = 0;
    int nextAccountNumber = 1001;
    int choice;
    
    // Load data from file at startup
    ifstream inFile("bank_data.txt");
    if (inFile.is_open()) {
        inFile >> totalAccounts >> nextAccountNumber;
        for (int i = 0; i < totalAccounts; i++) {
            inFile >> accountNumber[i];
            inFile.ignore();
            getline(inFile, accountHolderName[i]);
            getline(inFile, accountType[i]);
            inFile >> balance[i];
        }
        inFile.close();
    }
    
    cout << "\n========================================" << endl;
    cout << "   WELCOME TO SIMPLE BANKING SYSTEM" << endl;
    cout << "========================================" << endl;
    
    while (true) {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. Display All Accounts" << endl;
        cout << "6. Exit" << endl;
        cout << "===============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        // CREATE NEW ACCOUNT
        if (choice == 1) {
            if (totalAccounts >= 50) {
                cout << "\nBank is full! Cannot create more accounts." << endl;
            } else {
                cout << "\n===== CREATE NEW ACCOUNT =====" << endl;
                cout << "Enter Account Holder Name: ";
                cin.ignore();
                getline(cin, accountHolderName[totalAccounts]);
                
                cout << "Enter Account Type (Savings/Current): ";
                getline(cin, accountType[totalAccounts]);
                
                cout << "Enter Initial Deposit Amount: $";
                cin >> balance[totalAccounts];
                
                if (balance[totalAccounts] < 0) {
                    cout << "\nInvalid amount!" << endl;
                } else {
                    accountNumber[totalAccounts] = nextAccountNumber;
                    cout << "\nAccount created successfully!" << endl;
                    cout << "Your Account Number is: " << nextAccountNumber << endl;
                    nextAccountNumber++;
                    totalAccounts++;
                    
                    // Save to file after creating account
                    ofstream outFile("bank_data.txt");
                    outFile << totalAccounts << " " << nextAccountNumber << endl;
                    for (int i = 0; i < totalAccounts; i++) {
                        outFile << accountNumber[i] << endl;
                        outFile << accountHolderName[i] << endl;
                        outFile << accountType[i] << endl;
                        outFile << balance[i] << endl;
                    }
                    outFile.close();
                }
            }
        }
        
        // DEPOSIT MONEY
        else if (choice == 2) {
            int accNum;
            double amount;
            int found = -1;
            
            cout << "\nEnter Account Number: ";
            cin >> accNum;
            
            // Search for account
            for (int i = 0; i < totalAccounts; i++) {
                if (accountNumber[i] == accNum) {
                    found = i;
                    break;
                }
            }
            
            if (found == -1) {
                cout << "\nAccount not found!" << endl;
            } else {
                cout << "Enter amount to deposit: $";
                cin >> amount;
                
                if (amount > 0) {
                    balance[found] = balance[found] + amount;
                    cout << "\nSuccessfully deposited $" << amount << endl;
                    cout << "New Balance: $" << balance[found] << endl;
                    
                    // Save to file after deposit
                    ofstream outFile("bank_data.txt");
                    outFile << totalAccounts << " " << nextAccountNumber << endl;
                    for (int i = 0; i < totalAccounts; i++) {
                        outFile << accountNumber[i] << endl;
                        outFile << accountHolderName[i] << endl;
                        outFile << accountType[i] << endl;
                        outFile << balance[i] << endl;
                    }
                    outFile.close();
                } else {
                    cout << "\nInvalid amount!" << endl;
                }
            }
        }
        
        // WITHDRAW MONEY
        else if (choice == 3) {
            int accNum;
            double amount;
            int found = -1;
            
            cout << "\nEnter Account Number: ";
            cin >> accNum;
            
            // Search for account
            for (int i = 0; i < totalAccounts; i++) {
                if (accountNumber[i] == accNum) {
                    found = i;
                    break;
                }
            }
            
            if (found == -1) {
                cout << "\nAccount not found!" << endl;
            } else {
                cout << "Enter amount to withdraw: $";
                cin >> amount;
                
                if (amount <= 0) {
                    cout << "\nInvalid amount!" << endl;
                } else if (amount > balance[found]) {
                    cout << "\nInsufficient balance!" << endl;
                    cout << "Current balance: $" << balance[found] << endl;
                } else {
                    balance[found] = balance[found] - amount;
                    cout << "\nSuccessfully withdrawn $" << amount << endl;
                    cout << "Remaining Balance: $" << balance[found] << endl;
                    
                    // Save to file after withdrawal
                    ofstream outFile("bank_data.txt");
                    outFile << totalAccounts << " " << nextAccountNumber << endl;
                    for (int i = 0; i < totalAccounts; i++) {
                        outFile << accountNumber[i] << endl;
                        outFile << accountHolderName[i] << endl;
                        outFile << accountType[i] << endl;
                        outFile << balance[i] << endl;
                    }
                    outFile.close();
                }
            }
        }
        
        // CHECK BALANCE
        else if (choice == 4) {
            int accNum;
            int found = -1;
            
            cout << "\nEnter Account Number: ";
            cin >> accNum;
            
            // Search for account
            for (int i = 0; i < totalAccounts; i++) {
                if (accountNumber[i] == accNum) {
                    found = i;
                    break;
                }
            }
            
            if (found == -1) {
                cout << "\nAccount not found!" << endl;
            } else {
                cout << "\n========== ACCOUNT DETAILS ==========" << endl;
                cout << "Account Number    : " << accountNumber[found] << endl;
                cout << "Account Holder    : " << accountHolderName[found] << endl;
                cout << "Account Type      : " << accountType[found] << endl;
                cout << "Current Balance   : $" << balance[found] << endl;
                cout << "=====================================" << endl;
            }
        }
        
        // DISPLAY ALL ACCOUNTS
        else if (choice == 5) {
            if (totalAccounts == 0) {
                cout << "\nNo accounts found in the system!" << endl;
            } else {
                cout << "\n========== ALL ACCOUNTS ==========" << endl;
                for (int i = 0; i < totalAccounts; i++) {
                    cout << "\nAccount " << (i + 1) << ":" << endl;
                    cout << "  Account Number : " << accountNumber[i] << endl;
                    cout << "  Name           : " << accountHolderName[i] << endl;
                    cout << "  Type           : " << accountType[i] << endl;
                    cout << "  Balance        : $" << balance[i] << endl;
                }
                cout << "==================================" << endl;
            }
        }
        
        // EXIT
        else if (choice == 6) {
            cout << "\nThank you for using Simple Banking System!" << endl;
            cout << "Goodbye!" << endl;
            break;
        }
        
        // INVALID CHOICE
        else {
            cout << "\nInvalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    string name;
    double balance;

public:
    BankAccount() {
        accountNumber = 0;
        name = "";
        balance = 0.0;
    }

    BankAccount(int accNum, string accName, double initialBalance) {
        accountNumber = accNum;
        name = accName;
        balance = initialBalance;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    void setAccountNumber(int accNum) {
        accountNumber = accNum;
    }

    string getName() {
        return name;
    }

    void setName(string accName) {
        name = accName;
    }

    double getBalance() {
        return balance;
    }

    void setBalance(double accBalance) {
        balance = accBalance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        balance -= amount;
    }

    void displayBalance() {
        cout << fixed << setprecision(2);
        cout << "Your current balance is $" << balance << "." << endl;
    }
};

BankAccount accounts[100];
int accountCount = 0;

int generateAccountNumber() {
    return 100000 + rand() % 900000;
}

void createAccount() {
    if (accountCount >= 100) {
        cout << "Account limit reached!" << endl;
        return;
    }

    string customerName;
    double initialBalance;

    cout << "Enter your name: ";
    getline(cin, customerName);

    cout << "Enter your initial balance: ";
    cin >> initialBalance;

    int newAccountNumber = generateAccountNumber();

    accounts[accountCount] = BankAccount(newAccountNumber, customerName, initialBalance);

    cout << fixed << setprecision(2);
    cout << "Congratulations " << customerName << "! You have successfully opened your new bank account with an initial balance of $" << initialBalance << ". Your account number is " << newAccountNumber << "." << endl;

    accountCount++;
}

void depositMoney() {
    int accNum;
    cout << "Enter the account number: ";
    cin >> accNum;

    int index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].getAccountNumber() == accNum) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "No account number exists!" << endl;
        return;
    }

    double depositAmount;
    cout << "Enter the amount that you would like to deposit: ";
    cin >> depositAmount;

    accounts[index].deposit(depositAmount);

    cout << fixed << setprecision(2);
    cout << "Congratulations " << accounts[index].getName() << "! You have successfully deposited the amount of $" << depositAmount << " in your account #" << accNum << ". Your current balance is $" << accounts[index].getBalance() << "." << endl;
}

void withdrawMoney() {
    int accNum;
    cout << "Enter the account number: ";
    cin >> accNum;

    int index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].getAccountNumber() == accNum) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "No account number exists!" << endl;
        return;
    }

    double withdrawAmount;
    cout << "Enter the amount that you would like to withdraw: ";
    cin >> withdrawAmount;

    accounts[index].withdraw(withdrawAmount);

    cout << fixed << setprecision(2);
    cout << "Congratulations " << accounts[index].getName() << "! You have successfully withdrawn the amount of $" << withdrawAmount << " in your account #" << accNum << ". Your current balance is $" << accounts[index].getBalance() << "." << endl;
}

void displayBalance() {
    int accNum;
    cout << "Enter the account number: ";
    cin >> accNum;

    int index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].getAccountNumber() == accNum) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "No account number exists!" << endl;
        return;
    }

    accounts[index].displayBalance();
}

void displayMenu() {
    cout << "\n***************Welcome to Chase***************" << endl;
    cout << "Please choose one of the following operations" << endl;
    cout << "1- Create a new bank account with an initial balance" << endl;
    cout << "2- Deposit Money to an Account" << endl;
    cout << "3- Withdraw Money from an Account" << endl;
    cout << "4- Display Current Balance of an Account" << endl;
    cout << "0- Exit" << endl;
    cout << "Choice: ";
}

int main() {
    srand(time(0));

    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        if (choice == 0) {
            cout << "Thank you for banking with Chase! Goodbye!" << endl;
            break;
        }

        switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            depositMoney();
            break;
        case 3:
            withdrawMoney();
            break;
        case 4:
            displayBalance();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << "Press any key to return to Main Menu!" << endl;
        cin.get();
    }

    return 0;
}
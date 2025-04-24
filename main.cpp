#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

class Transaction {
private:
    string type;
    double amount;
    string timestamp;

    string getCurrentTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        string timeStr(dt);
        return timeStr.substr(0, timeStr.length() - 1);
    }

public:
    Transaction(string t, double a) {
        type = t;
        amount = a;
        timestamp = getCurrentTime();
    }

    void display() const {
        cout << type << " $" << fixed << setprecision(2) << amount << " on " << timestamp << endl;
    }
};

class Account {
protected:
    int accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(int num, double initial) {
        accountNumber = num;
        balance = initial;
        history.push_back(Transaction("Initial deposit", initial));
    }

    virtual void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
    }

    virtual void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds.\n";
            return;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount));
    }

    virtual void applyInterest() {} // Only for savings

    virtual string getType() const = 0;

    void showHistory() const {
        for (const auto& t : history) t.display();
    }

    double getBalance() const { return balance; }
    int getAccountNumber() const { return accountNumber; }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(int num, double initial) : Account(num, initial) {}
    string getType() const override { return "Checking"; }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int num, double initial) : Account(num, initial) {}
    void applyInterest() override {
        double interest = balance * 0.02;
        balance += interest;
        history.push_back(Transaction("Interest", interest));
    }
    string getType() const override { return "Savings"; }
};

class User {
private:
    string name;
    int userID;
    vector<Account*> accounts;

public:
    User(string n, int id) : name(n), userID(id) {}

    void addAccount(Account* acc) { accounts.push_back(acc); }

    void showAccounts() {
        for (size_t i = 0; i < accounts.size(); ++i) {
            cout << i+1 << ". " << accounts[i]->getType() << " Account #" << accounts[i]->getAccountNumber()
                 << " - Balance: $" << fixed << setprecision(2) << accounts[i]->getBalance() << endl;
        }
    }

    Account* getAccount(int index) {
        if (index < 0 || index >= accounts.size()) return nullptr;
        return accounts[index];
    }
};

class Bank {
private:
    vector<User> users;
    int nextAccountNumber = 1001;
    int nextUserID = 1;

public:
    void createUser() {
        string name;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        users.push_back(User(name, nextUserID++));
        cout << "User created.\n";
    }

    void openAccount() {
        int userIndex;
        cout << "Enter your user index (0 - " << users.size()-1 << "): ";
        cin >> userIndex;
        if (userIndex < 0 || userIndex >= users.size()) {
            cout << "Invalid user.\n";
            return;
        }
        string type;
        double initial;
        cout << "Checking or Savings? ";
        cin >> type;
        cout << "Initial deposit: ";
        cin >> initial;
        Account* acc = nullptr;
        if (type == "Checking") acc = new CheckingAccount(nextAccountNumber++, initial);
        else if (type == "Savings") acc = new SavingsAccount(nextAccountNumber++, initial);
        else {
            cout << "Invalid type.\n";
            return;
        }
        users[userIndex].addAccount(acc);
        cout << type << " account opened.\n";
    }

    void userMenu() {
        int index;
        cout << "Enter user index: ";
        cin >> index;
        if (index < 0 || index >= users.size()) {
            cout << "Invalid index.\n";
            return;
        }
        User& u = users[index];
        while (true) {
            cout << "1. Show accounts\n2. Deposit\n3. Withdraw\n4. Show history\n5. Exit\nChoice: ";
            int choice;
            cin >> choice;
            if (choice == 5) break;
            int accIndex;
            u.showAccounts();
            cout << "Select account (1-n): ";
            cin >> accIndex;
            Account* acc = u.getAccount(accIndex - 1);
            if (!acc) {
                cout << "Invalid account.\n";
                continue;
            }
            double amt;
            switch (choice) {
                case 1: break; // Already shown
                case 2:
                    cout << "Amount to deposit: ";
                    cin >> amt;
                    acc->deposit(amt);
                    break;
                case 3:
                    cout << "Amount to withdraw: ";
                    cin >> amt;
                    acc->withdraw(amt);
                    break;
                case 4:
                    acc->showHistory();
                    break;
                default:
                    cout << "Invalid.\n";
            }
        }
    }
};

int main() {
    Bank bank;
    while (true) {
        cout << "\nBankSim++\n1. Create User\n2. Open Account\n3. User Menu\n4. Exit\nChoice: ";
        int option;
        cin >> option;
        if (option == 4) break;
        switch (option) {
            case 1: bank.createUser(); break;
            case 2: bank.openAccount(); break;
            case 3: bank.userMenu(); break;
            default: cout << "Invalid option.\n";
        }
    }
    return 0;
}

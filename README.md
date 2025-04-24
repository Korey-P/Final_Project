# Final_Project
## Pseudocode

```plaintext
CLASS Transaction
    PRIVATE:
        type: string
        amount: double
        timestamp: string
    PUBLIC:
        FUNCTION Constructor(t, a)
            SET type TO t
            SET amount TO a
            SET timestamp TO current system time
        FUNCTION display()
            PRINT type + " $" + amount + " on " + timestamp
END CLASS

CLASS Account
    PROTECTED:
        accountNumber: integer
        balance: double
        history: list of Transaction
    PUBLIC:
        FUNCTION Constructor(num, initial)
            SET accountNumber TO num
            SET balance TO initial
            ADD new Transaction("Initial deposit", initial) to history
        FUNCTION deposit(amount)
            INCREASE balance by amount
            ADD new Transaction("Deposit", amount) to history
        FUNCTION withdraw(amount)
            IF amount > balance THEN
                PRINT "Insufficient funds"
            ELSE
                DECREASE balance by amount
                ADD new Transaction("Withdraw", amount) to history
        FUNCTION applyInterest() 
            // Only used in SavingsAccount
        FUNCTION getType() RETURNS string
            RETURN account type (defined in subclass)
        FUNCTION showHistory()
            FOR each transaction t in history
                CALL t.display()
        FUNCTION getBalance() RETURNS double
            RETURN balance
        FUNCTION getAccountNumber() RETURNS integer
            RETURN accountNumber
END CLASS

CLASS CheckingAccount EXTENDS Account
    PUBLIC:
        FUNCTION Constructor(num, initial)
            CALL Account constructor
        FUNCTION getType()
            RETURN "Checking"
END CLASS

CLASS SavingsAccount EXTENDS Account
    PUBLIC:
        FUNCTION Constructor(num, initial)
            CALL Account constructor
        FUNCTION applyInterest()
            CALCULATE interest = balance * 0.02
            INCREASE balance by interest
            ADD new Transaction("Interest", interest) to history
        FUNCTION getType()
            RETURN "Savings"
END CLASS

CLASS User
    PRIVATE:
        name: string
        userID: integer
        accounts: list of Account
    PUBLIC:
        FUNCTION Constructor(n, id)
            SET name TO n
            SET userID TO id
        FUNCTION addAccount(account)
            ADD account to accounts
        FUNCTION showAccounts()
            FOR each account a in accounts
                PRINT account type, number, and balance
        FUNCTION getAccount(index)
            RETURN account at index
END CLASS

CLASS Bank
    PRIVATE:
        users: list of User
        nextAccountNumber: integer
        nextUserID: integer
    PUBLIC:
        FUNCTION Constructor()
            SET nextAccountNumber TO 1001
            SET nextUserID TO 1
        FUNCTION createUser()
            ASK for user name
            CREATE new User with nextUserID
            INCREMENT nextUserID
            ADD user to users
        FUNCTION openAccount()
            ASK for user index
            ASK for account type (Checking or Savings)
            ASK for initial deposit
            CREATE new account with nextAccountNumber
            INCREMENT nextAccountNumber
            ADD account to selected user's account list
        FUNCTION userMenu()
            ASK for user index
            WHILE user is active:
                DISPLAY menu options (deposit, withdraw, history, etc.)
                ASK for choice
                PERFORM selected action on chosen account
END CLASS

FUNCTION main()
    CREATE Bank object
    WHILE program is running:
        DISPLAY main menu (Create User, Open Account, User Menu, Exit)
        ASK for choice
        CALL corresponding Bank method
END FUNCTION

#include "Bank.h"

/**
 * std::string _bank_name;
 * int _user_count;
 * Account* _users;
 */


/**
 * Empty constructor
 * give the bank_name as "not_defined"
 * give nullptr for pointers
 * give 0 as _users_count
 */
Bank::Bank() {
    this->_bank_name = "not defined";
    this->_users = nullptr;
    this->_user_count = 0;
}

/**
 * Constructor
 *
 *
 * @param bank_name name of this bank
 * @param users pointer to hold users of this bank
 * @param user_count number of users this bank has
*/
Bank::Bank(std::string bank_name, Account *const users, int user_count) {
    this->_bank_name = bank_name;
    this->_user_count = user_count;
    this->_users = new Account[user_count];
    for(int i=0 ; i<user_count ; ++i){
        this->_users[i] = users[i];
    }
}

/**
 * Destructor
 *
 * Do not forget to free the space you have created(This assignment does not use smart pointers)
 */
Bank::~Bank() {
    delete[] this->_users;
}

/**
 * Copy constructor(Deep copy)
 *
 * @param rhs The Bank to be copied
 */
Bank::Bank(const Bank &rhs) {
    this->_bank_name = rhs._bank_name;
    this->_user_count = rhs._user_count;
    this->_users = new Account[_user_count];
    for(int i=0 ; i<rhs._user_count ; ++i){
        this->_users[i] = rhs._users[i];
    }
}

/**
 * You should deep copy the content of the second bank
 * Merge two banks
 * If both banks has a user with the same id, Transactions of these users will be merged in to the same Account
 * For example:
 * Bank1 has [1,2] id users
 * Bank2 has [2,3] id users
 *
 * Bank1 after += operator will have [1,2,3] id users
 * User with id 2 will have its transactions histories merged
 *
 * Transactions with of the users with the same id should be merged and updated
 * @param rhs Merged Bank
 * @return this Bank
 */
Bank &Bank::operator+=(const Bank &rhs) {
    if(this == &rhs){
        return *this;
    }

    int newUserCount = this->_user_count;
    bool foundFlag;
    Account* newUsersFromThis = new Account[this->_user_count];
    Account* newUsersFromRhs = new Account[rhs._user_count];

    for(int i=0; i<this->_user_count ; ++i){
        foundFlag = false;
        for(int j=0; j<rhs._user_count ; j++){
            if(this->_users[i] == rhs._users[j]){
                foundFlag = true;
                Account* mergedAccount = new Account(this->_users[i]);
                *mergedAccount += rhs._users[j];
                newUsersFromThis[i] = *mergedAccount;
                break;
            }
        }
        if(!foundFlag){
            newUsersFromThis[i] = this->_users[i];
        }
    }

    for(int i=0; i<rhs._user_count ; ++i){
        foundFlag = false;
        for(int j=0; j<this->_user_count ; j++){
            if(rhs._users[i] == this->_users[j]){
                foundFlag = true;
                break;
            }
        }
        if(!foundFlag){
            newUsersFromRhs[i] = rhs._users[i];
            newUserCount++;
        }
    }

    Account* totalUsers = new Account[newUserCount];

    for(int i=0 ; i<newUserCount ; ++i){
        if(i<this->_user_count){
            totalUsers[i] = this->_users[i];
        } else {
            totalUsers[i] = rhs._users[i-this->_user_count];
        }
    }

    delete[] newUsersFromThis;
    delete[] newUsersFromRhs;
    delete[] this->_users;

    this->_user_count = newUserCount;
    this->_users = totalUsers;

    return *this;
}

/**
 * Add a new account to Bank
 *
 * If the newly added user already exists in this Bank merge their Transactions
 *
 * @param new_acc new account to add to bank
 * @return this Bank
 */
Bank &Bank::operator+=(const Account &new_acc) {

    if(new_acc == Account())
        return *this;

    bool foundFlag = false;
    for (int i = 0; i < this->_user_count; ++i) {
        if(this->_users[i] == new_acc){
            foundFlag = true;
            this->_users[i] += new_acc;
            break;
        }
    }
    if(!foundFlag){
        int i=0;
        Account* newAccounts = new Account[this->_user_count+1];
        for (i = 0; i < this->_user_count; ++i) {
            newAccounts[i] = this->_users[i];
        }
        newAccounts[i] = new_acc;

        delete[] this->_users;

        this->_users = newAccounts;
        this->_user_count = this->_user_count+1;
    }

    return *this;
}

/** Indexing operator overload
 *
 * Return the Account with the given id
 *
 * If there is no Account with the given id return the first element
 *
 * @param account_id id of the Account
 * @return if given id exist in the bank return the account, else return the first account
 *
 */
Account &Bank::operator[](int account_id) {
    for (int i = 0; i < this->_user_count; ++i) {
        if(this->_users[i] == account_id){
            return this->_users[i];
        }
    }

    return this->_users[0];
}

/**
 * Stream overload.
 * all the accounts will be between 01-01-2019 and 31-12-2019
 * What to stream
 * bank_name"tab"number of users who are eligible for a loan"tab"total balance of the bank
 *
 * A user is safe for a loan if and only if that user did not have any negative balance for 2 or more consecutive months
 * For example, let's say our bank named as "banana" has two users
 *
 * User A's balance for each month is as given
 *
 * January - 0
 * February - 0
 * March - 100
 * April - -20
 * May - -30
 * June - 40
 * July - 60
 * August - 0
 * September - 0
 * October - 0
 * November - 0
 * December - 0
 *
 * This user is not eligible because in April and May his/her balance was negative(consecutive)
 * You still have to add 150 to the total balance of the bank
 * User B's balance for each month is as given
 *
 * January - 0
 * February - 0
 * March - 100
 * April - -20
 * May - 40
 * June - -30
 * July - 60
 * August - 0
 * September - 0
 * October - 0
 * November - 0
 * December - 0
 *
 * This user is eligible because negative balances were not consecutive
 * You will also add 150 to the total balance of the bank
 *
 * your output will be as
 * banana   1   300
 */
std::ostream &operator<<(std::ostream &os, const Bank &bank) {
    int eligibleCount = 0;
    double totalBalance = 0;

    struct tm some_date = {0};

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 118; some_date.tm_mon = 11; some_date.tm_mday = 31;
    time_t date1 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 0; some_date.tm_mday = 31;
    time_t date2 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 1; some_date.tm_mday = 28;
    time_t date3 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 2; some_date.tm_mday = 31;
    time_t date4 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 3; some_date.tm_mday = 30;
    time_t date5 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 4; some_date.tm_mday = 31;
    time_t date6 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 5; some_date.tm_mday = 30;
    time_t date7 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 6; some_date.tm_mday = 31;
    time_t date8 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 7; some_date.tm_mday = 31;
    time_t date9 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 8; some_date.tm_mday = 30;
    time_t date10 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 9; some_date.tm_mday = 31;
    time_t date11 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 10; some_date.tm_mday = 30;
    time_t date12 = mktime(&some_date);

    some_date.tm_hour = 23;   some_date.tm_min = 59; some_date.tm_sec = 59;
    some_date.tm_year = 119; some_date.tm_mon = 11; some_date.tm_mday = 31;
    time_t date13 = mktime(&some_date);


    time_t dates[] = {date1, date2, date3, date4, date5, date6, date7, date8, date9, date10, date11, date12, date13};
    bool previous;
    bool negative;

    for (int i = 0; i < bank._user_count; ++i) {
        previous = false;
        negative = false;
        for (int j = 0; j < 12; ++j) {
            if(bank._users[i].balance(dates[j], dates[j+1]+1) < 0){
                if(previous){
                    negative = true;
                    break;
                } else {
                    previous = true;
                }
            }
        }
        if(!negative){
            eligibleCount++;
        }
    }

    for (int i = 0; i < bank._user_count; ++i) {
        totalBalance += bank._users[i].balance();
    }

    os<<bank._bank_name<<"\t"<<eligibleCount<<"\t"<<totalBalance<<"\n";

    return os;
}

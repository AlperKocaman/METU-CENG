#include "Account.h"

/**
 *
 * Private Fields
 *
 * int _id;
 * Transaction** _activity;
 * int* _monthly_activity_frequency;
 */

//TODO : do self assignment detection if needed
//TODO : check if the 2 pointers are given memory in heap(this->_activity = new Transaction* [12];this->_monthly_activity_frequency = new int[12];)
//TODO : release every resources before doing an assignment or before copy constructor

/**
 * Empty constructor
 * give the id as -1
 * give nullptr for pointers
 */
Account::Account(){
    this->_id = -1;
    this->_activity = nullptr;
    this->_monthly_activity_frequency = nullptr;
}

/**
 * Constructor
 *
 *
 * Note: The given activity array will have 12 Transaction*
 * Each of these Transaction* will represent a month from the 2019
 * Basicaly activity[0] will represent January
 *          activity[11] will represent February
 *          activity[11] will represent March
 *                      ...
 *          activity[10] will represent November
 *          activity[11] will represent December
 * activity[0] will only contain Transactions happened in January
 * However, be careful that Transactions inside of activity[i] will not be in sorted order
 * For Example: We are certain that activity[0] is containing Transactions happened in January 2019
 * But we are not sure which of them happened first.
 * I strongly suggest you to use a sorting algorithm while storing these Transaction to your object.
 * (Sorting by the date, So that you can directly use them in stream overload)
 * (You can use bubble sort)
 *
 * @param id id of this Account
 * @param activity 2d Transaction array first layers length is 12 for each month
 * @param monthly_activity_frequency how many transactions made in each month
*/
Account::Account(int id, Transaction** const activity, int* monthly_activity_frequency){
    if(activity == nullptr || monthly_activity_frequency == nullptr){
        this->_id = -1;
        this->_activity = nullptr;
        this->_monthly_activity_frequency = nullptr;
        return;
    }

    this->_id = id;
    this->_activity = new Transaction* [12];
    this->_monthly_activity_frequency = new int[12];

    for(int i=0 ; i<12 ; i++){
        Transaction* tempArray = activity[i];
        if(tempArray != nullptr){
            for(int j=0; j<monthly_activity_frequency[i] ; j++){
                int minTransaction = j;
                for (int k = j+1; k < monthly_activity_frequency[i] ; ++k) {
                    if(tempArray[k] < tempArray[minTransaction]) {
                        minTransaction = k;
                    }
                }
                Transaction tempTransaction = tempArray[j];
                tempArray[j] = tempArray[minTransaction];
                tempArray[minTransaction] = tempTransaction;
            }

            Transaction* monthArray = new Transaction[monthly_activity_frequency[i]];
            for(int l=0 ; l<monthly_activity_frequency[i] ; ++l){
                monthArray[l] = tempArray[l];
            }
            this->_activity[i] = monthArray;
            this->_monthly_activity_frequency[i] = monthly_activity_frequency[i];
        } else {
            this->_activity[i] = nullptr;
            this->_monthly_activity_frequency[i] = 0;
        }
    }
}

/**
 * Destructor
 *
 * Do not forget to free the space you have created(This assignment does not use smart pointers)
 */
Account::~Account(){
    if(this->_activity != nullptr) {
        for (int i = 0; i < 12; ++i) {
            if (this->_activity[i] != nullptr)
                delete[] _activity[i];
        }
        delete[] this->_activity;
    }

    delete[] this->_monthly_activity_frequency;
}

/**
 * Copy constructor(Deep copy)
 *
 * @param other The Account to be copied
 */
Account::Account(const Account& rhs){
    this->_id = rhs._id;
    this->_activity = new Transaction* [12];
    this->_monthly_activity_frequency = new int[12];
    for(int i=0; i<12 ; ++i){
        this->_activity[i] = new Transaction[rhs._monthly_activity_frequency[i]];
        for(int j=0 ; j<rhs._monthly_activity_frequency[i] ; ++j){
            this->_activity[i][j] = rhs._activity[i][j];
        }
        this->_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];
    }
}

/**
 * Copy constructor(Deep copy)
 *
 * This copy constructors takes two time_t elements
 * Transactions of the old Account will be copied to new Account
 * if and only if they are between these given dates
 * Given dates will not be included.
 *
 * @param rhs The Account to be copied
 * @param start_date Starting date for transaction to be copied.
 * @param end_date Ending date for transactions to be copied.
 */
Account::Account(const Account& rhs, time_t start_date, time_t end_date){

    if(rhs._activity == nullptr || rhs._monthly_activity_frequency == nullptr){
        this->_id = -1;
        this->_activity = nullptr;
        this->_monthly_activity_frequency = nullptr;
        return;
    }

    this->_id = rhs._id;
    this->_activity = new Transaction* [12];
    this->_monthly_activity_frequency = new int [12];

    bool timeFlag = true;

    for(int i=0 ; i<12 ; ++i){
        Transaction* monthlyTransactions = nullptr;
        int monthlyTransactionNumber = 0;
        for (int j = 0; j < rhs._monthly_activity_frequency[i] && timeFlag; ++j) {
            if(rhs._activity[i][j] < start_date+1){
                continue;
            }
            else if(rhs._activity[i][j] < end_date){
                monthlyTransactionNumber++;
            }
            else{
                timeFlag = false;
            }
        }
        if(monthlyTransactionNumber != 0){
            monthlyTransactions = new Transaction[monthlyTransactionNumber];
            int transactionCounter = 0;
            for (int j = 0; j < rhs._monthly_activity_frequency[i]; ++j) {
                if(rhs._activity[i][j] < start_date+1){
                    continue;
                }
                else if(rhs._activity[i][j] < end_date){
                    monthlyTransactions[transactionCounter++] = rhs._activity[i][j];
                }
            }
        }
        this->_activity[i] = monthlyTransactions;
        this->_monthly_activity_frequency[i] = monthlyTransactionNumber;
    }
}

/**
 * Move constructor
 *
 * @param rhs Account which you will move the resources from
 */
Account::Account(Account&& rhs){
    this->_id = rhs._id;
    this->_monthly_activity_frequency = rhs._monthly_activity_frequency;
    this->_activity = rhs._activity;
    rhs._activity = nullptr;
    rhs._monthly_activity_frequency = nullptr;
    rhs._id = -1;
}

/**
 * Move assignment operator
 *
 * @param rhs Account which you will move the resources from
 */
Account& Account::operator=(Account&& rhs){
    if(this == &rhs){
        return *this;
    }
    if(this->_activity != nullptr) {
        for (int i = 0; i < 12; ++i) {
            delete[] this->_activity[i];
        }
    }
    delete[] this->_activity;
    delete[] this->_monthly_activity_frequency;

    this->_id = rhs._id;
    this->_monthly_activity_frequency = rhs._monthly_activity_frequency;
    this->_activity = rhs._activity;

    rhs._activity = nullptr;
    rhs._monthly_activity_frequency = nullptr;
    rhs._id = -1;

    return *this;
}

/**
 * Assignment operator
 * deep copy
 *
 * @param rhs Account to assign
 * @return this account
 */
Account& Account::operator=(const Account& rhs){
    if(this == &rhs){
        return *this;
    }

    if(this->_activity != nullptr) {
        for (int i = 0; i < 12; ++i) {
            delete[] this->_activity[i];
        }
    }
    delete[] this->_activity;
    delete[] this->_monthly_activity_frequency;

    this->_id = rhs._id;
    this->_activity = new Transaction* [12];
    this->_monthly_activity_frequency = new int[12];
    for(int i=0; i<12 ; ++i){
        if(rhs._monthly_activity_frequency[i] != 0) {
            this->_activity[i] = new Transaction[rhs._monthly_activity_frequency[i]];
            for (int j = 0; j < rhs._monthly_activity_frequency[i]; ++j) {
                this->_activity[i][j] = rhs._activity[i][j];
            }
        } else {
            this->_activity[i] = nullptr;
        }
        this->_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];
    }
    return *this;
}

/**
 * Equality comparison overload
 *
 * This operator checks only id of the Account
 *
 * @param rhs The Account to compare
 * @return returns true if both ids are same false otherwise
 */

bool Account::operator==(const Account& rhs) const{
    return this->_id == rhs._id;
}
/**
 * Equality comparison overload
 *
 * This operator checks only id of the Account
 *
 * @param id to compare
 * @return returns true if both ids are same false othervise
 */
bool Account::operator==(int id) const{
    return this->_id == id;
}

/**
 * sum and equal operator
 * Add Transactions of two Accounts
 * You have to add transactions in correct places in your _activity array
 * Note: Remember that _activity[0] is always January and _activity[11] is always December
 * (This information also holds for every other month)
 *
 * You can have Transactions with the same date
 *
 * @param rhs Account which take new Transactions from
 * @return this Account after adding new Transactions
 */
Account& Account::operator+=(const Account& rhs){
    //TODO : self check?? I  didn't implement it since we have transactions with same date and not implementing this one might ease the testing process.

    if(rhs._activity == nullptr || rhs._monthly_activity_frequency == nullptr){
        return *this;
    }

    else if(this->_activity == nullptr || this->_monthly_activity_frequency == nullptr){

        delete[] this->_activity;
        delete[] this->_monthly_activity_frequency;

        this->_activity = new Transaction* [12];
        this->_monthly_activity_frequency = new int[12];
        for(int i=0; i<12 ; ++i){
            if(rhs._monthly_activity_frequency[i] != 0) {
                this->_activity[i] = new Transaction[rhs._monthly_activity_frequency[i]];
                for (int j = 0; j < rhs._monthly_activity_frequency[i]; ++j) {
                    this->_activity[i][j] = rhs._activity[i][j];
                }
            } else {
                this->_activity[i] = nullptr;
            }
            this->_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];
        }
        return *this;
    }

    Transaction** newActivity = new Transaction*[12];
    int* newMonthlyActivityFrequency = new int[12];

    for(int i=0; i<12 ; ++i){
        newMonthlyActivityFrequency[i] = this->_monthly_activity_frequency[i] + rhs._monthly_activity_frequency[i];
    }

    int thisAccount = 0, rhsAccount = 0;

    for(int i=0; i<12 ; i++){
        Transaction* thisMonth = this->_activity[i];
        Transaction* rhsMonth = rhs._activity[i];

        if(thisMonth == nullptr && rhsMonth == nullptr){
            newActivity[i] = nullptr;
        } else if(thisMonth == nullptr) {
            newActivity[i] = new Transaction[rhs._monthly_activity_frequency[i]];
            for(int j=0 ; j<rhs._monthly_activity_frequency[i] ; ++j){
                newActivity[i][j] = rhs._activity[i][j];
            }
        } else if(rhsMonth == nullptr) {
            newActivity[i] = new Transaction[this->_monthly_activity_frequency[i]];
            for(int j=0 ; j<this->_monthly_activity_frequency[i] ; ++j){
                newActivity[i][j] = this->_activity[i][j];
            }
        } else{
            thisAccount = 0;
            rhsAccount = 0;
            newActivity[i] = new Transaction[newMonthlyActivityFrequency[i]];
            for(int j=0; j<newMonthlyActivityFrequency[i]; ++j){
                if(thisAccount == this->_monthly_activity_frequency[i]){
                    newActivity[i][j] = rhs._activity[i][rhsAccount];
                    rhsAccount++;
                } else if(rhsAccount == rhs._monthly_activity_frequency[i]){
                    newActivity[i][j] = this->_activity[i][thisAccount];
                    thisAccount++;
                }
                else if(this->_activity[i][thisAccount] < rhs._activity[i][rhsAccount]){
                    newActivity[i][j] = this->_activity[i][thisAccount];
                    thisAccount++;
                } else {
                    newActivity[i][j] = rhs._activity[i][rhsAccount];
                    rhsAccount++;
                }
            }
        }
    }

    if(this->_activity != nullptr) {
        for (int i = 0; i < 12; ++i) {
            delete[] this->_activity[i];
        }
    }
    delete[] this->_activity;
    delete[] this->_monthly_activity_frequency;

    this->_activity = newActivity;
    this->_monthly_activity_frequency = newMonthlyActivityFrequency;

    return *this;
}

/**
 * How much money Account has(Sum of Transaction amounts)
 *
 *
 * @return total amount of the money of the account
 */
double Account::balance(){
    double totalAmount = 0;
    if(this->_activity == nullptr || this->_monthly_activity_frequency == nullptr){
        return totalAmount;
    }
    for(int i=0 ; i<12 ; ++i){
        for (int j = 0; j < this->_monthly_activity_frequency[i]; j++) {
            totalAmount = this->_activity[i][j] + totalAmount;
        }
    }
    return totalAmount;
}

/**
 * How much money Account has at the end of given date
 *
 * Given date will not be included.
 * @param end_date You will count the amounts until this given date(not inclusive)
 * @return Total amount the Account has until given date
 */
double Account::balance(time_t end_date){
    double totalAmount = 0;
    if(this->_activity == nullptr || this->_monthly_activity_frequency == nullptr){
        return totalAmount;
    }
    bool timeFlag = true;
    for(int i=0 ; i<12 && timeFlag ; ++i){
        for (int j = 0; j < this->_monthly_activity_frequency[i] && timeFlag; j++) {
            if (this->_activity[i][j] < end_date) {
                totalAmount = this->_activity[i][j] + totalAmount;
            } else {
                timeFlag = false;
            }
        }
    }
    return totalAmount;
}


/**
 * How much money Account between given dates
 * Given dates will not be included.
 *
 * @param end_date You will count the amounts between given dates(not inclusive)
 * @return Total amount the Account has between given dates
 * You will only count a Transaction amount if and only if it occurred between given dates
 */
double Account::balance(time_t start_date, time_t end_date){
    double totalAmount = 0;
    if(this->_activity == nullptr || this->_monthly_activity_frequency == nullptr){
        return totalAmount;
    }
    bool timeFlag = true;
    for(int i=0 ; i<12 && timeFlag ; ++i){
        for (int j = 0; j < _monthly_activity_frequency[i] && timeFlag; j++) {
            if (this->_activity[i][j] < start_date+1) {
                continue;
            } else if (this->_activity[i][j] < end_date) {
                totalAmount = this->_activity[i][j] + totalAmount;
            } else {
                timeFlag = false;
            }
        }
    }
    return totalAmount;
}

/**
 * Stream overload.
 *
 *
 *
 * What to stream
 * Id of the user
 * Earliest Transaction amount"tab"-"tab"hour:minute:second-day/month/year(in localtime)
 * Second earliest Transaction amount"tab"-"tab"hour:minute:second-day/month/year(in localtime)
 * ...
 * Latest Transaction amount"tab-tab"hour:minute:second-day/month/year(in localtime)
 *
 * Note: _activity array will only contain dates from January 2019 to December 2019
 * Note: Transactions should be in order by date
 * Note: either of _monthly_activity_frequency or _activity is nullptr
 * you will just stream
 * -1
 * @param os Stream to be used.
 * @param Account to be streamed.
 * @return the current Stream
 */

std::ostream& operator<<(std::ostream& os, const Account& account){
    if(account._activity != nullptr && account._monthly_activity_frequency != nullptr) {
        os<<account._id<<"\n";
        for (int i = 0; i < 12; ++i) {
            if(account._activity[i] != nullptr) {
                for (int j = 0; j < account._monthly_activity_frequency[i]; ++j) {
                    os << account._activity[i][j];
                }
            }
        }
    }
    else{
        os<<-1<<"\n";
    }

    return os;
}

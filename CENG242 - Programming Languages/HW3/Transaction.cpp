#include "Transaction.h"

/**
 * Empty constructor
 * give -1 to everything
 */
Transaction::Transaction(){
    this->_amount = -1;
    this->_date = -1;
}

/**
 * Constructor
 *
 * @param amount The value of Transaction(Can be negative or positive)
 * @param date Transaction date
*/
Transaction::Transaction(double amount, time_t date){
    this->_amount = amount;
    this->_date = date;
}

/**
 * Copy Constructor.
 *
 * @param rhs The Transaction to be copied.
 */
Transaction::Transaction(const Transaction& rhs){
    this->_amount = rhs._amount;
    this->_date = rhs._date;
}

/**
 * Compare two Transaction based on their date
 *
 * @param rhs Compared Transaction
 * @return If current Transaction happened before the given Transaction return true
 * else return false
 */
bool Transaction::operator<(const Transaction& rhs) const{
    return this->_date < rhs._date;
}

/**
 * Compare two Transaction based on their date
 *
 * @param date Compared date
 * @return If current Transaction happened after the given Transaction return true
 * else return false
 */
bool Transaction::operator>(const Transaction& rhs) const{
    return this->_date > rhs._date;
}

/**
 * Compare a Transaction with a given date
 *
 * @param date Compared date
 * @return If current Transaction happened before the given date return true
 * else return false
 */
bool Transaction::operator<(const time_t date) const{
    return this->_date < date;
}

/**
 * Compare a Transaction with a given date
 *
 * @param date Compared date
 * @return If current Transaction happened after the given date return true
 * else return false
 */
bool Transaction::operator>(const time_t date) const{
    return this->_date > date;

}

/**
 * Sum the value of two Transaction amounts
 *
 * @param rhs The transaction to sum over
 * @return The output of the summation in double format
 */
double Transaction::operator+(const Transaction& rhs){
    // TODO: is total number saved in the transaction?
    return this->_amount + rhs._amount;
}

/**
 * Sum the value of a Transaction with another double
 *
 * @param add The amount to sum over
 * @return The output of the summation in double format
 */
double Transaction::operator+(const double add){
    // TODO: is total number saved in the transaction?
    return this->_amount + add;
}

/**
 * Assignment operator
 *
 * @param rhs Transaction to assign
 * @return this Transaction
 */
Transaction& Transaction::operator=(const Transaction& rhs){
    this->_amount = rhs._amount;
    this->_date = rhs._date;
    return *this;
}

/**
 * Stream overload
 *
 * What to stream:
 * Transaction amount"tab-tab"hour:minute:second-day/month/year(in localtime)
 *
 * @param os Stream to be used.
 * @param transaction Transaction to be streamed.
 * @return the current Stream
 */
std::ostream& operator<<(std::ostream& os, const Transaction& transaction){
    struct tm * transactionTime = localtime(&(transaction._date));
    os<<transaction._amount<<"\t"<<"-"<<"\t"<<transactionTime->tm_hour<<":"<<transactionTime->tm_min<<":"<<transactionTime->tm_sec
    <<"-"<<transactionTime->tm_mday<<"/"<<(transactionTime->tm_mon+1)<<"/"<<(transactionTime->tm_year+1900)<<"\n";
    return os;
}
#ifndef _HW3_H
#define _HW3_H
#include <iostream>
#include <string>
#include <vector>
#include <utility>  // use just for std::pair< >
#include <fstream>

#define MAX_LOAD_FACTOR 0.65
#define EMPTY "EMPTY"
#define DELETED "DELETED"


class AccessControl
{
public:
	AccessControl(int table1Size, int table2Size);
	~AccessControl();

	int addUser(std::string username, std::string pass);
	int addUsers(std::string filePath);
	int delUser(std::string username, std::vector<std::string>& oldPasswords);
	int changePass(std::string username, std::string oldpass, std::string newpass);

	int login(std::string username, std::string pass);
	int logout(std::string username);

	float printActiveUsers();
	float printPasswords();
private:

	int  getNewTableSize (int tableSize) const ; //returns the expanded table size
	bool isPrime( int number) const ; // checks whether given number is prime or not

	//<<your hash class>> activeUsers;	// hash(username) -> username
	
	std::string* table2 ;
	int n2 ;// number of inserted entries for table2,used in calculations about load factor
	int table2size ;
	double loadFactorforTable2() const ;
	void expandTable2() ;

	//<<your hash class>> regUsers;  		// hash(username) -> username,password

	std::pair<std::string , std::string>* table1 ;
	int n1 ;// number of inserted entries for table1,used in calculations about load factor
	int table1size ;
	double loadFactorforTable1() const ;
	void expandTable1() ;

	int hashFunction(std::string key, int tableSize, int i) {
	   int length = key.length();
	   int newK = 0;
	   for (int j = 0; j < length; j++)
	     newK += (int) key[j];

		 // hash function 1 -> (newK % tableSize)
		 // hash function 2 -> (newK * tableSize - 1) % tableSize)

	   return ((newK % tableSize) + i * ((newK * tableSize - 1) % tableSize)) % tableSize;
	}
};

#endif
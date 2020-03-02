#include "hw3.h"

//Table1 and n1 is used for register users ,delete users and change password.

//Table2 and n2 is used for login and logout. 

AccessControl::AccessControl(int table1Size, int table2Size) {

	int i = 0 ;

	table1size = table1Size ; // class' private member table1size is initialized

	table2size = table2Size ; // class' private member table2size is initialized

	n1 = 0 ; n2 = 0 ;         //number of elements that both tables have is initially 0  

	table1 = new std::pair<std::string , std::string>[table1Size] ; //vector can also be used but I choose this one

	table2 = new std::string[table2Size] ; 

	//make all rows empty in both tables

	for( i= 0 ; i < table1Size ; i++ ) { 

		table1[i].first  = EMPTY ;
		table1[i].second = EMPTY ; 
	} 

	for( i= 0 ; i < table2Size ; i++ ) 

		table2[i] = EMPTY ;
	
}

AccessControl::~AccessControl() { 

	//since both tables constructed with "new" and allocate memory in heap,they should be deleted.

	n1 = 0 ;
	n2 = 0 ;
	delete[] table1 ;
	delete[] table2 ;

}

int AccessControl::addUser(std::string username, std::string pass) {

	int value = -1 ; //actually -1 is not needed, "int value ;"  line is sufficient.

	for( int i = 0 ; i < table1size ; i++) {

		value = hashFunction( username , table1size , i ) ;

		if( table1[value].first == username ) //username is already exist in table.

			return 0 ;

		if( table1[value].first == EMPTY || table1[value].first == DELETED ) { //proper index to insert user

			table1[value].first = username ;

			table1[value].second = pass ;

			n1 ++ ; //number of inserted elements incremented

			if( loadFactorforTable1() > MAX_LOAD_FACTOR ) 

				expandTable1() ; //helper function to expand for table1

			return 1 ;
		}
	}

	return 0 ;
}

int AccessControl::addUsers(std::string filePath) {

	int number_of_registers = 0 ; //this will be return value and keeps the number of successfully added users.

	std::ifstream ifs(filePath.c_str()); //constructs ifstream object ifs and associate with the file 

	if(!ifs) return 0 ; //file couldn't be opened.

	std::string line ;

	std::string username ;

	std::string password ;

	while ( ifs.good() ) { //take inputs from file if file is good(haven't reached end of the file yet).

		getline(ifs,line,' ') ; //take username

		username = line ;

		getline(ifs,line) ;	//take password

    	password = line ;

    	number_of_registers += addUser(username,password) ; //if user can be added successfully,addUser return 1 and 1 is added

	}		

	return number_of_registers ;
}

int AccessControl::delUser(std::string username, std::vector<std::string>& oldPasswords) {

	int value = -1 ; 

	int flag = 0 ; //keeps if user is found and successfully deleted

	for( int i = 0 ; i < table1size ; i++ ) {

		value = hashFunction( username , table1size , i ) ;

		if( table1[value].first == EMPTY ) return flag ; //if more registers with this username,it should be in this index.
														 //But it is empty,so function can be finished here. 
		else if( table1[value].first != username ) continue ; //another user or already deleted user exist in that index 
															  //entries with given username still may exist. 
		table1[value].first = DELETED ; //found an entry

		oldPasswords.push_back( table1[value].second ) ;

		table1[value].second = DELETED ; 

		flag = 1 ; n1 -- ;	//user if found so flag is 1,it is deleted so n1 is decremented .
	}

	return flag ;
}

int AccessControl::changePass(std::string username, std::string oldpass, std::string newpass) {

	std::string pass = "" ;

	int value = -1 ;

	for( int i = 0 ; i < table1size ; i++ ) {

		//this for loop is for finding the latest password of requested user.

		value = hashFunction( username , table1size , i ) ;

		if( table1[value].first == EMPTY ) break ;

		else if( table1[value].first != username ) continue ;

		pass = table1[value].second ;

	}

	if( pass == oldpass ) {

		for( int j = 0 ; j < table1size ; j++ ) { 

			//instead of using a for loop to find an index to insert changed password to table1,i value can be used.
			//value = hashFunction( username , table1size , ++i ) ; with only this line instead of for loop.
			//However,this way is more safer.

			value = hashFunction( username , table1size , j ) ;

			if( table1[value].first == EMPTY || table1[value].first == DELETED ) break ; //suitable place is found
		}

		table1[value].first = username ;

		table1[value].second = newpass ;

		n1 ++ ;	//new insertion to table1.	

		if( loadFactorforTable1() > MAX_LOAD_FACTOR )

			expandTable1() ;

		return 1 ;
	} 

	return 0 ;
}

int AccessControl::login(std::string username, std::string pass) {

	std::string current_pass = "" ;

	int value = -1 ;

	for( int i = 0 ; i < table1size ; i++ ) { //finding the latest password like in the changePass function.

		value = hashFunction( username , table1size , i ) ;

		if( table1[value].first == EMPTY ) break ;

		else if( table1[value].first != username ) continue ;

		current_pass = table1[value].second ;

	}

	if( current_pass == pass ) {

		for( int j = 0 ; j < table2size ; j++ ) { //if given pass is true,insert the user into the table2 if not already exist.

			value = hashFunction( username , table2size , j ) ;

			if(table2[value] == username) return 0 ;

			if( table2[value] == EMPTY || table2[value] == DELETED ) { 

				table2[value] = username ;

				n2 ++ ;

				if( loadFactorforTable2() > MAX_LOAD_FACTOR )

					expandTable2() ;

				return 1 ;

			}

		}

	} 

	return 0 ;	
}

int AccessControl::logout(std::string username) {

	int value = -1 ;

	for( int i = 0 ; i < table2size ; i++ ) {

		value = hashFunction( username , table2size , i ) ;

		if( table2[value] == EMPTY ) return 0 ; //user not exist

		if( table2[value] != username ) continue ;

		table2[value] = DELETED ; //user is found and deleted.

		n2-- ;

		return 1 ;
	}

	return 0 ; //if user is not found but also empty index is not found(deleted rows may fill the rest of the table),this line returns 0.
}

float AccessControl::printActiveUsers() {

	for(int i=0 ; i< table2size ;i++)

		std::cout<<table2[i]<<std::endl ;

	return loadFactorforTable2() ;
}

float AccessControl::printPasswords() {

	for(int i=0 ; i< table1size ;i++) 

		std::cout<<table1[i].first<<" "<<table1[i].second<<std::endl ;		

	return loadFactorforTable1() ;
}

int AccessControl::getNewTableSize (int tableSize) const { //helper for finding the new size of the table.

	for( int i = 2*tableSize+1 ; ;i+=2) // 2*tableSize+1 is odd , i+=2 is sufficient.

		if( isPrime(i) ) return i ;
}

bool AccessControl::isPrime( int number) const { //helper for deciding if number is prime or not.

	if( number%2 == 0) return false ;

	for( int i= 3 ; i*i <= number ; i+=2 ) 

		if( number%i == 0) return false ;

	return true ;
}

double AccessControl::loadFactorforTable1() const {

	return (double)n1 / (double)table1size ;
}

double AccessControl::loadFactorforTable2() const {

	return (double)n2 / (double)table2size ;
}

void AccessControl::expandTable1() {

	int i = 0;

	int value1 = -1 ;

	int value2 = -1 ;

	int oldSize = table1size ;

	std::pair<std::string , std::string>* oldTable = table1 ;

	table1size = getNewTableSize(oldSize) ;

    n1 = 0 ;  

	table1 = new std::pair<std::string , std::string>[table1size] ;

	//new table1 with new size is constructed now.Rows are initialized below. 

	for( i= 0 ; i < table1size ; i++ ) {

		table1[i].first  = EMPTY ;
		table1[i].second = EMPTY ; 
	} 

	for( i=0; i<oldSize ; i++) { //this loop traverse from top to down and find a nonempty index in the oldTable. 

		if(oldTable[i].first == DELETED || oldTable[i].first == EMPTY ) 

			continue ; //this row is deleted or empty in oldTable,no need to rehash.

        int j = 0 ;

		do{	

			value1 = hashFunction( oldTable[i].first , oldSize , j ) ; //in order to find the first occurance of this user in the oldTable.
 																	   //after first,it will give 2'nd,3'rd ...n'th..(in the expected order).
																	 //it is in the do-while loop since we should check at least 1 time. 	
			j++ ;

			if( oldTable[value1].first == DELETED ) continue ;

			if( oldTable[value1].first != oldTable[i].first )  continue ; 

			for(int k=0 ; k < table1size ; k++ ) { //this loop is for finding a suitable place in the new expanded table.

				value2 = hashFunction( oldTable[i].first , table1size , k ) ;

				if( table1[value2].first == EMPTY ) { 	

					table1[value2].first = oldTable[value1].first ;

					table1[value2].second = oldTable[value1].second ;

					n1 ++ ;

					oldTable[value1].first = DELETED ; oldTable[value1].second = DELETED ;

					break ;

				}

			}

		}while( oldTable[value1].first != EMPTY && j != oldSize ) ;

	}

	delete [] oldTable ;

}

void AccessControl::expandTable2() {

	int i = 0 ,j = 0;

	int value = -1 ;

	int oldSize = table2size ;

	std::string* oldTable = table2 ;

	table2size = getNewTableSize(oldSize) ;

    n2 = 0 ;  

    //new table2 with new size is constructed now.Rows are initialized below. 

	table2 = new std::string[table2size] ;

	for( i= 0 ; i < table2size ; i++ ) {

		table2[i] = EMPTY ; 
	} 

	for( i=0; i<oldSize ; i++) {

		if(oldTable[i] == DELETED || oldTable[i] == EMPTY ) 

			continue ; //this row is deleted or empty in oldTable,no need to rehash.

		for(j = 0 ; j< table2size ; j++) { //this row should be rehashed.

			value = hashFunction( oldTable[i] , table2size , j ) ;

			if(table2[value] == EMPTY ) {

				table2[value] = oldTable[i] ;

				n2++ ;

				break ;
			}

		}

	}

	delete [] oldTable ;
}


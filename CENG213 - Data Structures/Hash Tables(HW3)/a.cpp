#include <iostream>

int hashFunction(std::string key, int tableSize, int i) {
	   int length = key.length();
	   int newK = 0;
	   for (int j = 0; j < length; j++)
	     newK += (int) key[j];

		 // hash function 1 -> (newK % tableSize)
		 // hash function 2 -> (newK * tableSize - 1) % tableSize)

	   return ((newK % tableSize) + i * ((newK * tableSize - 1) % tableSize)) % tableSize;
	}

int main(){

	std::cout<<hashFunction("Vale",17,1)<<std::endl ;

	return 0 ; 	
}

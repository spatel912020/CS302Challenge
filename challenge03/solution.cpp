// Challenge 06: Palindrome Permutation

/*
 *	Shreyank Patel
 *	2/3/2020
 *	Lab Section: 8:00am Monday
 */
#include <stdio.h>
#include <iostream>
#include <unordered_set>
#include <sstream>

using namespace std; 

int main(int argc, char *argv[]) {

	string line; 
	unordered_multiset<char> test_string;
	unordered_multiset<char>::iterator it;
	//Read line from cin until you reach the end
	while(getline(cin, line)){
		//Set up variable for each test case 
		bool hasOdd = false;
		bool isPalindrome = true;
		
		//Read each char from line into multiset
		for(char c: line){
			//Exclude special characters
			if(c != '?' && c != '.' && c != ' ')test_string.insert(char(tolower(c)));
		}
		//Set iterator to the begining for set
		it = test_string.begin();
	
		//Loop through set until the end or set or until exit case
		for( ; it!= test_string.end(); ){
			//Check if char is present in set odd number of times
			if(test_string.count(*it)%2 != 0){
				//Only one set of odd number char is allowed in a palindrome 
				if(!hasOdd){
					hasOdd = true;
					it++;
				}
				else{
					//Print out statement and exit for loop 
					cout<<"\""<<line<<"\" is not a palindrome permutation"<<endl;
					isPalindrome = false;
					it = test_string.end();
				}
			}	
			else	it++;
			
		}
		if(isPalindrome)	cout<<"\""<<line<<"\" is a palindrome permutation"<<endl;
		//Clear set for next line of cin
		test_string.clear();	
	}
	return 0;
}


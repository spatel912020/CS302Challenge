// Challenge 01: Rotating Arrays; null solution
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <math>
using namespace std;
int main(int argc, char *argv[]){
		
		stringstream ss;
		string temp;
		int n_elements, element;
		cin>>n_elements;
		set <int> my_set;
		set <int>::iterator it; 
		int num1, num2, diff; 
		while(getline(cin, temp)){
			ss.clear();
			ss<<temp;
			ss>>element;
			my_set.insert(element);
		}
		it = my_set.begin();

		for(it; it != my_set.end(); it++){
			num1 = *it;
			num2 = *(it++);
			if (diff > abs(num1-num2)){
				diff = abs(num1-num2);
			}
		}

	return 0;
}


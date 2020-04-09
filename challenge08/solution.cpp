// Challenge 08: Adding List-Based Integers
#include <iostream>
#include <cstdio>
#include <sstream>
#include "d_list.cpp"

using namespace std; 

int main(int argc, char *argv[]) {
    
	string interger1, interger2;
	string total, line; 
	stringstream ss;

	while(getline(cin, line)){
		ss.clear();
		ss<<line;
		ss>>interger1>>interger2;

		dList *int1_list = new dList();
		dList *int2_list = new dList();
		dList *sum_list = new dList();
		for(char const &c: interger1){
			int1_list->push_back(c, '0');

		}
		for(char const &c: interger2){
			int2_list->push_back(c, '0');
		}
		dNode *temp = int1_list->sentinel->prev;
		dNode *temp2 = int2_list->sentinel->prev;
		while(temp != int1_list->sentinel && temp2 != int2_list->sentinel){
			int int_num1 = 0, int_num2 = 0;
			int remainder_int = 0; 
			int sum = 0;
			int_num1 = temp->digit - 48;
			int_num2 = temp2->digit - 48;
			remainder_int = temp->remainder - 48;
			sum = int_num1 + int_num2 + remainder_int;
			char summed = sum%10 + 48;
			sum_list->push_front(summed, '0');
			//if(temp->prev != int1_list->sentinel){
				temp->prev->remainder = char(sum/10 + 48);
			//}
			temp = temp->prev;
			temp2 = temp2->prev;
		}
		if(temp == int1_list->sentinel && temp2 == int2_list->sentinel && int1_list->sentinel->remainder != '0'){
			sum_list->push_front(int1_list->sentinel->remainder, '0');
		}
		if(temp != int1_list->sentinel){
			while(temp != int1_list->sentinel){
				int int1_num1 = temp->digit -48;
				int remainder = temp->remainder - 48;
				char summed = (int1_num1 + remainder)%10 +48;
				sum_list->push_front(summed, '0');
				if(temp->prev == int1_list->sentinel && ((int1_num1 + remainder)/10) != 0){
					char summed = (int1_num1 + remainder)/10 +48;
					sum_list->push_front(summed, '0');
				}
				temp = temp->prev;
			}
		}
		if(temp2 != int2_list->sentinel){
			while(temp2 != int2_list->sentinel){
				int int2_num1 = temp2->digit - 48;
				int remainder = temp->remainder - 48;
				char summed = (int2_num1 + remainder)%10 +48;
				sum_list->push_front(summed, '0');
				if(temp2->prev == int2_list->sentinel && ((int2_num1 + remainder)/10) != 0){
					char summed = (int2_num1 + remainder)/10 +48;
					sum_list->push_front(summed, '0');
				}
				temp2 = temp2->prev;
			}
		}
		dNode *iterator = sum_list->sentinel->next;
		while(iterator != sum_list->sentinel){
			cout<<iterator->digit;
			iterator = iterator->next;
		}
		cout<<endl;
		delete int1_list;
		delete int2_list;
		delete sum_list;
	}
	return 0;
}



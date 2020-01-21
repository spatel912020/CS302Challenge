// Challenge 01: Rotating Arrays; null solution
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;
int main(int argc, char *argv[]){
		
		stringstream ss;
		string temp, temp2;
		int num_element, num_rotation;
		string dir; 
		vector <int> my_array;
		while(getline(cin, temp)){
			ss.clear();
			ss<<temp;
			ss>>num_element>>num_rotation>>dir;
			int element;
			getline(cin, temp2);
			ss.clear();
			ss<<temp2;
			while(ss >> element){
				my_array.push_back(element);
			}
			if(num_element == num_rotation){
				cout<<my_array[0];
				for(int i = 1; i < int(my_array.size()); i++){
					cout<<" "<<my_array[i];
				}
				//cout<<endl;
				//break;
			}
			if(num_rotation > num_element){
				num_rotation = num_rotation - num_element;
			}
			int start; 
			if(dir == "L" && num_element!= num_rotation){
				start = num_rotation;
				cout<<my_array[start];
				start++;
				while(start != num_rotation){
					if(start > num_element-1){
						start = 0;
					}
					cout<<" "<<my_array[start];
					start++;
				}
			//	cout<<endl;
			}
			else if(dir == "R" && num_element!= num_rotation){
				start = my_array.size() - num_rotation;
				cout<<my_array[start];
				start++;
				while(start != int(my_array.size()-num_rotation)){
					if(start > num_element-1){
						start = 0;
					}
					cout<<" "<<my_array[start];
					start++;
				}
			//	cout<<endl;
			}

			cout<<endl;
			my_array.clear();
		}
	return 0;
}


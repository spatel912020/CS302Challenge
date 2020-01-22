// Challenge 01: Rotating Arrays; null solution
#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <iterator>
#include <utility>
using namespace std;
int main(int argc, char *argv[]){
		
		stringstream ss;
		string temp;
		int n_elements, element;
		set <int> my_set;
		set <int>::iterator set_it; 
		multimap <int, pair< int, int > > my_map;
		multimap <int, pair< int, int > >::iterator map_it;
		int num1, num2, diff; 
		while(getline(cin, temp)){
			ss.clear();
			ss<<temp;
			ss>>n_elements;
			ss.clear();
			getline(cin, temp);
			ss<<temp;
			while(ss>>element){
				my_set.insert(element);
			}
				set_it = my_set.begin();
				int count = 0;
				for( ; set_it != my_set.end(); set_it++){
					if(count == 0){
						num1 = *set_it;
						num2 = *next(set_it,1);
						diff = abs(num1-num2);
						my_map.insert(pair<int, pair<int, int> > (diff, pair<int, int> (num1, num2)));
						count = 1;
					}
					else{
						count = 0;
					}
				}
				map_it = my_map.begin();
				int temp3 = map_it->first;
				while(temp3 == map_it->first){
					cout<<map_it->second.first<<" "<<map_it->second.second<<" ";
					map_it++;
				}
				cout<<endl;
				my_set.clear();
				my_map.clear();
		}
	return 0;
}


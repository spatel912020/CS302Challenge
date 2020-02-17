// Challenge 04: kth smallest number
// Name: Shreyank Patel
// Section: Monday 8:00 AM
// 
// Determines if vector is a max heap, create min heap and find kth smallest number
//

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <stdlib.h>

using namespace std;

//Function declaration
void percolate_down(vector<int> &heap, int index);
int Pop(vector<int> &h); 

int main(int argc, char *argv[]) {

	int element, size, k, parent;
	bool isMax;
	vector<int> my_heap;
	stringstream ss;
	string line; 
	
	while(getline(cin, line)){	
		ss.clear();
		ss<<line;
		ss>>size>>k;
		isMax = true;
		getline(cin, line);
		ss.clear();
		ss<<line;
		int i = 0; 
		
		//read each num from line and pushback onto my_heap
		while(ss>>element){	 
			my_heap.push_back(element);

			//Check to determine if the numbers read in are max heap
			if(i != 0 && isMax == true){
				//parent = (i-1)/2
				parent = (i-1)/2;
				//if the child is greater than parent, set isMax to false;
				if(my_heap[i] > my_heap[parent]){
					isMax = false;
				}
			}
			//increment i to calculate next element's parent
			i++;
		}
		
		//Percolate down on the vector to make a min heap
		for (int i = my_heap.size()/2-1; i >= 0; i--) percolate_down(my_heap, i);
		//Pop k-2 times
		for(int i = 0; i <= k-2; i++){
			(Pop(my_heap));
		}		
		//Print statement
		if(isMax){
			cout<<"Y  "<<my_heap[0]<<endl;
		}		
		else{
			cout<<"N  "<<my_heap[0]<<endl;
		}
		//clear vector for next test case 
		my_heap.clear();
	}
	return 0;
}

//Compare current node to children nodes and swap if necessary
void percolate_down(vector<int> &my_heap, int index){
	int left, right;
	int tmp;

    while (1) {                
		left = index*2+1;
		right = left+1;
		
		//if left is greater than heap size - exit
		if (left >= int(my_heap.size())) return;

		//Check if right is greater than heap size or left child is less than right child 
		if (right >= int(my_heap.size()) || my_heap[left] <= my_heap[right]) {
			//If left child is less than index  swap heap[index] and  heap[left]
			if (my_heap[left] < my_heap[index]) {
				tmp = my_heap[left];
				my_heap[left] = my_heap[index];
				my_heap[index] = tmp;
				index = left;
			} else {
				return;
			}
		//Check if right chil is less than index swap heap[index] and heap[right]
		} else if (my_heap[right] < my_heap[index]) {
			tmp = my_heap[right];
			my_heap[right] = my_heap[index];
			my_heap[index] = tmp;
			index = right;
		} else {
			return;
		}
	}
}

//Pop the root of heap and put last element at root and percolate down
int Pop(vector<int> &h) 
{
	int retval;
	  
	if (h.empty()) {
		cerr << "Error: Heap is empty\n";
		exit(1);
	}
	retval = h[0];
	h[0] = h[int(h.size())-1];
	h.pop_back();
	if (int(h.size()) == 0) return retval;
	percolate_down(h, int(0));
	return retval;
}

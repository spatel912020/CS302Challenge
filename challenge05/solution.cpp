// Challenge 05: Graph Paths

/* Shreyank Patel
 * 02/17/1999
 *
 */

#include <vector>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

bool searchMatrix(vector< vector<int> > graph, int rows, int cols, int target);
// Main Execution

int main(int argc, char *argv[]) {
	
	//martix for look up
	vector < vector<int> > my_graph;
	stringstream ss;
	int num_edges;
	int num_paths;
	int num_graph = 1;
//	my_graph.resize(1);
//	my_graph[0].resize(1, 0);
	char source, destination;
	int int_source, int_destination;
	string line;

	while(getline(cin, line)){
		my_graph.resize(1);
		my_graph[0].resize(1, 0);
		ss.clear();
		ss<<line;
		ss>>num_edges;
		while(num_edges){
			getline(cin, line);
			ss.clear();
			ss<<line;
			ss>>source>>destination;
			int_source = source - 65;
			int_destination = destination - 65;
			if(int_source > int(my_graph.size()-1)){
				my_graph.resize(int_source+1);
				if(int_destination > int(my_graph[int_source].size()-1)){
					my_graph[int_source].resize(int_destination+1, 0);
					my_graph[int_source][int_destination] = 1; 
				}
				else	my_graph[int_source][int_destination] = 1;
			}
			else if(int_destination > int(my_graph[int_source].size()-1)){
				my_graph[int_source].resize(int_destination+1, 0);
				my_graph[int_source][int_destination] = 1; 

			}
			else	my_graph[int_source][int_destination] = 1; 
			num_edges--;
		}
		getline(cin, line);
		ss.clear();
		ss<<line;
		ss>>num_paths;
		
		while(num_paths){	
			getline(cin, line);
			ss.clear();
			ss<<line;
			ss>>source>>destination;
			int_source = source - 65;
			int_destination = destination - 65;
			bool isPath;
			isPath = searchMatrix(my_graph, int_source, int_destination, int_destination);
			/*if(int_source > int(my_graph.size()-1)){	
				cout<<"In Graph "<<num_graph<<" there is no path from "<<source<<" to "<<destination<<endl;
			}
			else if(int_destination > int(my_graph[int_source].size()-1)){	
				cout<<"In Graph "<<num_graph<<" there is no path from "<<source<<" to "<<destination<<endl;
			}
			else{
				if(my_graph[int_source][int_destination] == 1){
					cout<<"In Graph "<<num_graph<<" there is a path from "<<source<<" to "<<destination<<endl;
				}
				else	cout<<"In Graph "<<num_graph<<" there is no path from "<<source<<" to "<<destination<<endl;
			}*/
			if(isPath){	
				cout<<"In Graph "<<num_graph<<" there is a path from "<<source<<" to "<<destination<<endl;
			}
			else{
				cout<<"In Graph "<<num_graph<<" there is no path from "<<source<<" to "<<destination<<endl;
			}
			num_paths--;
		}
		my_graph.clear();
		num_graph++;
	}

	return 0;
}

bool searchMatrix(vector< vector<int> > graph, int rows, int cols, int target){
	bool isTrue = false;
	if(rows > int(graph.size()-1)){
		return isTrue;
	}
	if(cols > int(graph[rows].size()-1)){
		return isTrue;
	}
	if(graph[rows][cols] == 1){
		if(target == cols)	return true;
	}
	for(int  j= 0; j < int(graph[rows].size()); j++){
		if(graph[rows][j] == 1){
			if(graph.size() > j && target <= j){	
			//	cout<<rows<<"--"<<j<<endl;
				isTrue = searchMatrix(graph, j, target, target);	}
		}
	}
	return isTrue;
}

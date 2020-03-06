// Challenge 6: Minimum Spanning Tree
// Shreyank Patel
// 03/02/2020
// Section 8:00 am to 11:00 am

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <sstream>

using namespace std;

// Main Execution

int main(int argc, char *argv[]) {

	int n_verticles = 0, element = 0;
	int cur_verticle = 0;
	int distance = 0;
	bool same_destination = false;
	vector < vector <int> >graph_matrix;
	set<int> visited_verticles;
	set<string> ordered_verticles;
	set<string>::iterator ordered_it;
	int total_path = 0;
	multimap <int, string> edges;
	multimap <int, string>::iterator edges_it;
	multimap <int, string>::iterator temp;
	
	string edge = " ";
	char source = ' ', destination = ' ';
	stringstream ss;
	int input = 0;
	
	//# of verticles;
	while(cin >> n_verticles){
		if(input != 0){
			cout<<endl;
		}
		input++;
		total_path = 0;
		graph_matrix.resize(n_verticles);
		//Construct adjacency matrix
		for(int i = 0; i < n_verticles; i++){
			graph_matrix[i].resize(n_verticles, -1);
			//Fill in the cols of the current row;
			for(int j = 0; j < n_verticles; j++){
				cin>>element;
				if(element != -1)	graph_matrix[i][j] = element;
			}
		}

		//Start at the first matrix entry @ graph_matrix[0][j]
		cur_verticle = 0;
		//Until all the verticles are not visited atleast once
		while(int(visited_verticles.size()) != n_verticles){
			for(int col = 0; col < n_verticles; col++){
				if(graph_matrix[cur_verticle][col] != -1){	
					same_destination = false;
					//Check if there is already a verticle in multimap going to same destination with larger distance
					for(edges_it = edges.begin(); edges_it != edges.end(); edges_it++){					
						//if yes - delete the verticle from multimap and add cur verticle into multimap because closer to same destination
						if(edges_it->first > graph_matrix[cur_verticle][col] && (edges_it->second)[1] == col+65){
							same_destination = true;
							distance = graph_matrix[cur_verticle][col];
							source = cur_verticle + 65;
							destination = col + 65;
							edge = source;
							edge += destination;
							temp = edges_it;
							temp--;
							edges.erase(edges_it);
							edges_it = temp;
							pair<int, string> temp(distance, edge);
							edges.insert(temp);
						}
					}
					//else add to multimap because different destination verticle
					if(!same_destination){	
						distance = graph_matrix[cur_verticle][col];
						source = cur_verticle + 65;
						destination = col + 65;
						if(edges.empty())	visited_verticles.insert(source - 65);
						edge = source;
						edge += destination;
						pair<int, string> temp(distance, edge);
						edges.insert(temp);
					}	
				}
			}
	
			//First in multimap 
			edges_it = edges.begin();
			while(visited_verticles.find((edges_it->second)[1] - 65) != visited_verticles.end()){
				edges.erase(edges_it);
				edges_it = edges.begin();
			}
			//add distance to total_path value 
			total_path += edges_it->first;
			string append = "";
			//Insert verticle into set with smaller of the two verticle first followed by the other
			if(edges_it->second[0] > edges_it->second[1]){
				append = edges_it->second[1];
				append += edges_it->second[0];
			}
			else{
				append = edges_it->second;
			}
			ordered_verticles.insert(append);
			
			visited_verticles.insert(cur_verticle);
			//Cur verticle = the destination verticle of first element in multimap
			cur_verticle = (edges_it->second)[1] - 65;
			//Insert into vistied_verticles 
			visited_verticles.insert(cur_verticle);
			temp = edges_it;
			temp--;
			edges.erase(edges_it);
			edges_it = temp;
		}
		cout<<total_path<<endl;
		for(ordered_it = ordered_verticles.begin(); ordered_it != ordered_verticles.end(); ordered_it++){
			cout<<*ordered_it<<endl;
		}
		ordered_verticles.clear();
		edges.clear();
		graph_matrix.clear();
		visited_verticles.clear();
	}	
	return (0);

}


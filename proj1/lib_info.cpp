#include <iostream>
#include <iomanip>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;
/*
 * Shreyank Patel
 * Nicholas Hodge
 */

struct Song {
		string title;
		string artist;
		string album;
		string genre;
		int time;
		int track;
};

struct Album {
	map <int, Song*> songs;
	string name;
	int time;
	int nsongs;
};

struct Artist {
	map<string, Album*> albums;
	string name;
	int time;
	int nsongs;
};

Song* extract_info_from_string(string song);
string convert_time_to_string(int time);
int convert_time_to_int(string time);

int main(int argc, char*argv[]){
	
	//Check if two arguments are provided
	if(argc != 2){
		cerr<<"Not enough arguements provided"<<endl;
		return 0;
	}
	//Contains a map of all artist name and artist pointer
	map <string, Artist*> all_artist;
	
	// open input file 
	string filename;
	string line;
	filename = argv[1];
	ifstream fin;
	fin.open(filename.c_str());
	//if file open fails
	if(fin.fail()){
		cerr<<"Could not open file"<<endl;
		return 0;
	}

	//read in the data from the file and extract the info
	getline(fin, line);
	//create a new song with extracted data
	Song* song = extract_info_from_string(line);
	//create a new album with extracted data
	Album* album = new Album();
	//assign album data to the album variables
	album->name = song->album;
	album->time = song->time;
	album->nsongs = 1;
	//insert the song into the album
	album->songs.insert(pair<int, Song*>(song->track, song));	
	
	//create a new artist with extracted data
	Artist* artist = new Artist();
	//assign artist data to the artist variables
	artist->albums.insert(pair<string, Album*>(album->name, album));
	artist->name = song->artist;
	artist->time = song->time;
	artist->nsongs = 1;
	//insert artist into map of artists
	all_artist.insert(pair<string, Artist*>(artist->name, artist));

	//loop through remaining songs, while comparing them to the current songs to create albums and artists as needed	
	while(getline(fin, line)){
		Song* song = extract_info_from_string(line);
		map <string, Artist*>::iterator found_artist;
		found_artist = all_artist.find(song->artist);
		//if we can't find the artist, create a new album and artist and assign the song to them
		if(found_artist == all_artist.end()){			
			Album* album = new Album();
			
			album->songs.insert(pair<int, Song*>(song->track, song));
			album->name = song->album;
			album->time = song->time;
			album->nsongs = 1;

			Artist* artist = new Artist();
			
			artist->albums.insert(pair<string, Album*>(album->name, album));
			artist->name = song->artist;
			artist->time = song->time;
			artist->nsongs = 1;
			all_artist.insert(pair<string, Artist*>(artist->name, artist));
		}
		//if we found the artist, see if the album already exists
		else{

			found_artist->second->time += song->time;
			found_artist->second->nsongs += 1;
			//found artist, now check if album matches
			map <string, Album*>::iterator found_album;
			found_album = found_artist->second->albums.find(song->album);
			if(found_album == found_artist->second->albums.end()){
				//album not found so create new album
				Album *album = new Album();
				album->songs.insert(pair<int, Song*>(song->track, song));
				album->name = song->album;
				album->time = song->time;
				album->nsongs = 1;

				//all to artist album map
				found_artist->second->albums.insert(pair<string, Album*>(album->name, album));
				found_album = found_artist->second->albums.find(song->album);
				map <int, Song*>::iterator found_song;
				found_song = found_album->second->songs.find(song->track);
				//Didnt find song in album
				if(found_song == found_album->second->songs.end()){
					found_album->second->songs.insert(pair<int, Song*>(song->track, song));
					found_album->second->time += song->time;
					found_album->second->nsongs += 1;
				}
			}
			else{
				map <int, Song*>::iterator found_song;
				found_song = found_album->second->songs.find(song->track);
				//Didnt find song in album
				if(found_song == found_album->second->songs.end()){
					found_album->second->songs.insert(pair<int, Song*>(song->track, song));
					found_album->second->time += song->time;
					found_album->second->nsongs += 1;
				}
			}
		}
	}

	fin.close();

	map <string, Artist*>::iterator print_artist; 
	print_artist = all_artist.begin();
	string time_temp;
	//loop through the artists map
	for(print_artist; print_artist != all_artist.end(); print_artist++){
		time_temp = convert_time_to_string(print_artist->second->time);
		cout<<print_artist->first<<": "<<print_artist->second->nsongs<<", "<<time_temp<<endl;
		map<string, Album*>::iterator print_album; 
		print_album = print_artist->second->albums.begin();
		//loop through the albums map
		for(print_album; print_album != print_artist->second->albums.end(); print_album++){
			time_temp = convert_time_to_string(print_album->second->time);
			cout<<"        "<<print_album->first<<": "<<print_album->second->nsongs<<", "<<time_temp<<endl;
			map<int, Song*>::iterator print_song;
			print_song = print_album->second->songs.begin();
			//loop through the songs map
			for(print_song; print_song != print_album->second->songs.end(); print_song++){

				time_temp = convert_time_to_string(print_song->second->time);
				cout<<"                "<<print_song->first<<". "<<print_song->second->title<<": "<<time_temp<<endl;
			}
		}
	}

	return 0;
}

//Extract all info from a string and create a new song
Song* extract_info_from_string(string song){
	stringstream ss;
	ss.clear();
	string temp;
	Song* new_song = new Song();
	ss<<song;
	ss>>new_song->title>>temp>>new_song->artist>>new_song->album>>new_song->genre>>new_song->track;
	new_song->time = convert_time_to_int(temp);
	replace(new_song->title.begin(), new_song->title.end(), '_', ' ');
	replace(new_song->artist.begin(), new_song->artist.end(), '_', ' ');
	replace(new_song->album.begin(), new_song->album.end(), '_', ' ');
	replace(new_song->genre.begin(), new_song->genre.end(), '_', ' ');
	return new_song;
}

//Convert the time from a string to an int.
int convert_time_to_int(string time){
	stringstream ss; 
	ss.clear();
	string min, sec; 
	int find_colon = int(time.find(":"));
	int temp, tot_time = 0;
	min = time.substr(0, find_colon);
	sec = time.substr(find_colon+1, time.length());
	ss<<min;
	ss>>temp;
	tot_time = temp * 60;
	ss.clear();
	ss<<sec;
	ss>>temp;
	tot_time += temp;
	return tot_time;
}

//Convert the time from a int to a string.
string convert_time_to_string(int time){
	string tot_time = "" ;
	if(time%60 < 10){
		tot_time = to_string(time/60) + ":0" + to_string(time%60);
	}
	else	tot_time = to_string(time/60) + ":" + to_string(time%60);
	return tot_time;
}


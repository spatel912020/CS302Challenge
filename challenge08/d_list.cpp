#include <cstdlib>
#include <string>

using namespace std;

class dNode{
	public:
		char digit;
		char remainder;
		dNode *next;
		dNode *prev;
};

class dList{
	public:
		dList();
		~dList();
		void Clear();
		void push_back(char digit, char remainder);
		void push_front(char digit, char remainder);
		char pop_back();
		size_t Size();	
	
		dNode *sentinel;
		size_t size;
};

dList::dList(){
	dNode *s = new dNode;
	sentinel = s;
	sentinel->digit = ' ';
	sentinel->remainder = ' ';
	sentinel->next = sentinel;
	sentinel->prev = sentinel; 
	size = 0; 
}

dList::~dList(){
	Clear();
	delete sentinel;
}

void dList::Clear(){
	while(size != 0){
		pop_back();
	}
}

char dList::pop_back(){
	if(size == 0) return 'x';
	dNode *temp = sentinel->prev;
	dNode *temp2 = temp->prev;
	char temp_digit = temp->digit;
	//char temp_remainder = temp->remainder;

	sentinel->prev = temp2;
	temp2->next = sentinel;
	size--;
	delete temp;
	return temp_digit;
}

size_t dList::Size(){
	return size;
}

void dList::push_back(char digit, char remainder){
	dNode *temp = new dNode;
	temp->digit = digit;
	temp->remainder = remainder;
	if(size == 0){
		sentinel->next = temp;
		sentinel->prev = temp;
		temp->next = sentinel;
		temp->prev = sentinel;
		size++; 
		return;
	}
	temp->prev = sentinel->prev;
	sentinel->prev->next = temp;
	sentinel->prev = temp;
	temp->next = sentinel;
	size++;
}

void dList::push_front(char digit, char remainder){
	dNode *temp = new dNode;
	temp->digit = digit;
	temp->remainder = remainder;
	if(size == 0){
		sentinel->next = temp;
		sentinel->prev = temp;
		temp->next = sentinel;
		temp->prev = sentinel;
		size++; 
		return;
	}
	temp->next = sentinel->next;
	sentinel->next->prev = temp;
	sentinel->next = temp;
	temp->prev = sentinel;
	size++;
}

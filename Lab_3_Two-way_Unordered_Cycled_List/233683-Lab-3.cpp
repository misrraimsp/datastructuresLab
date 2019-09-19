#include<iostream>
#include <string>
#include <sstream>

using namespace std;


// Two-way unordered cycled list without sentinel
struct Element{
	int value;
	Element* next;
	Element* prev;
};

struct List2W{
	Element* hp;
};

void shiftLeft(List2W& l, int pos){
	if(l.hp == NULL) return;
	for(int i = 0; i < pos; i++) l.hp = l.hp->next;
}

void shiftRight(List2W& l, int pos){
	if(l.hp == NULL) return;
	for(int i = 0; i < pos; i++) l.hp = l.hp->prev;
}

void init(List2W& l){
	l.hp = NULL;
}

void insertHead(List2W& l, int x){
	//build new element
	Element* nh = new Element;
	nh->value = x;
	if(l.hp == NULL) { //empty list
		nh->next = nh;
		nh->prev = nh;
		l.hp = nh;
		return;
	}
	if(l.hp->next == l.hp) { //one-element list
		nh->next = l.hp;
		nh->prev = l.hp;
		l.hp->next = nh;
		l.hp->prev = nh;
		l.hp = nh;
		return;
	}
	//organize element connections
	nh->next = l.hp;
	nh->prev = l.hp->prev;
	//reorganize list connections
	l.hp->prev->next = nh; //first tail next
	l.hp->prev = nh; //then head prev
	l.hp = nh; //then newhead
}

bool deleteHead(List2W& l, int &value){
	if(l.hp == NULL) return false; //empty list
	Element* k = l.hp;
	if(l.hp->next == l.hp) { //one element list
		l.hp = NULL;
	}
	else {
		l.hp = l.hp->next;
		k->prev->next = l.hp;
		l.hp->prev = k->prev;
	}
	value = k->value;
	delete k;
	return true;
}

void deleteHead(List2W& l){
	if(l.hp == NULL) return; //empty list
	Element* k = l.hp;
	if(l.hp->next == l.hp) { //one element list
		l.hp = NULL;
	}
	else {
		l.hp = l.hp->next;
		k->prev->next = l.hp;
		l.hp->prev = k->prev;
	}
	delete k;
}

void insertTail(List2W& l, int x){
	insertHead(l, x);
	shiftLeft(l,1);
}

bool deleteTail(List2W& l, int &value){
	shiftRight(l,1);
	return deleteHead(l, value);
}

int findValue(List2W& l, int value){
	if(l.hp != NULL){
		int index = 0;
		Element* e = l.hp;
		do{
			if(e->value == value) return index;
			index++;
			e = e->next;
		}while(e != l.hp);
	}
	return -1;
}

void removeAllValue(List2W& l, int value){
	if(l.hp == NULL) return; //empty list
	while(l.hp != NULL && l.hp->value == value) deleteHead(l);
	if(l.hp != NULL){ //exists some elment != value
		Element* head = l.hp; //store the head
		do {
			shiftLeft(l,1);
			while(l.hp->value == value) deleteHead(l);
		} while(l.hp != head);
		l.hp = head;
	}
}

void showListFromHead(List2W& l){
	if(l.hp != NULL){//not empty list
		Element* s = l.hp;
		while(s->next != l.hp){
			cout << s->value << ",";
			s = s->next;
		}
		cout << s->value << ","; //show last element
	}
	cout << endl;
}

void showListFromTail(List2W& l){
	if(l.hp != NULL){//not empty list
		Element* s = l.hp->prev;
		while(s->prev != l.hp->prev){
			cout << s->value << ",";
			s = s->prev;
		}
		cout << s->value << ","; //show last element
	}
	cout << endl;
}

void clearList(List2W& l){
	while(l.hp != NULL) deleteHead(l);
}

void addList(List2W& l1,List2W& l2){
	if(l1.hp == l2.hp || l2.hp == NULL) return;
	if(l1.hp == NULL){
		l1.hp = l2.hp;
		l2.hp = NULL;
		return;
	}
	Element* t1p = l1.hp->prev;
	l1.hp->prev->next = l2.hp;
	l1.hp->prev = l2.hp->prev;
	l2.hp->prev = t1p;
	l1.hp->prev->next = l1.hp;
	l2.hp = NULL;
}

void showBool(bool val){
	if(val)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line; 
	string command;
	List2W *list;
	int currentL=0;
	int value;
	cout << "START" << endl;
	while(true){
		getline(cin,line);
		std::stringstream stream(line);
		stream >> command;
		if(line=="" || command[0]=='#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0]=toupper(command[0]);
		command[1]=toupper(command[1]);

		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}


		// zero-argument command
		if(isCommand(command,"DH")) //*
		{
			int retValue;
			bool retBool=deleteHead(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if(isCommand(command,"DT")) //*
		{
			int retValue;
			bool retBool=deleteTail(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"SH")) //*
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if(isCommand(command,"ST")) //*
		{
			showListFromTail(list[currentL]);
			continue;
		}

		if(isCommand(command,"CL")) //*
		{
			clearList(list[currentL]);
			continue;
		}

		if(isCommand(command,"IN")) //*
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;
		
		if(isCommand(command,"FV")) //*
		{
			int ret;
			ret=findValue(list[currentL],value);
			cout << ret << endl;
			continue;
		}

		if(isCommand(command,"RV")) //*
		{
			removeAllValue(list[currentL],value);
			continue;
		}


		if(isCommand(command,"AD")) //*
		{
			addList(list[currentL],list[value]);
			continue;
		}

		if(isCommand(command,"CH")) //*
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IH")) //*
		{
			insertHead(list[currentL],value);
			continue;
		}

		if(isCommand(command,"IT")) //*
		{
			insertTail(list[currentL],value);
			continue;
		}

		if(isCommand(command,"GO")) //*
		{
			list=new List2W[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}

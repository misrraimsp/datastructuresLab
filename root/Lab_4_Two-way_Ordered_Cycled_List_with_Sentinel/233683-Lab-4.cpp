#include<iostream>
#include <string>
#include <sstream>

using namespace std;


struct Element{
	int key;
	int value;
};

struct ElementLL{
	Element elem;
	ElementLL *next, *prev;
};

// Two-way ordered cycled list with sentinel
struct List2W{
	ElementLL *sentinel;
};

void init(List2W& l){
	l.sentinel=new ElementLL();
	l.sentinel->next=l.sentinel;
	l.sentinel->prev=l.sentinel;
}

void deleteHead(List2W& l){
	if(l.sentinel->next == l.sentinel) return;
	ElementLL* k = l.sentinel;
	l.sentinel->prev->next = l.sentinel->next;
	l.sentinel->next->prev = l.sentinel->prev;
	l.sentinel = l.sentinel->next;
	delete k;
}

void insertElem(List2W& l, Element elem){
	//build new elementLL
	ElementLL* newElemLL = new ElementLL();
	newElemLL->elem = elem;
	//look for the proper position to insert
	ElementLL* n = l.sentinel->next;//start looking on head
	if(n == l.sentinel){//empty list
		newElemLL->next = l.sentinel;
		newElemLL->prev = l.sentinel;
		l.sentinel->next = newElemLL;
		l.sentinel->prev = newElemLL;
		return;
	}
	while(n != l.sentinel && n->elem.key <= newElemLL->elem.key) n = n->next;
	if(n == l.sentinel){//insert as last element
		newElemLL->next = l.sentinel;
		newElemLL->prev = l.sentinel->prev;
		l.sentinel->prev->next = newElemLL;
		l.sentinel->prev = newElemLL;
		return;
	}
	//insert somewhere in the middle
	newElemLL->next = n;
	newElemLL->prev = n->prev;
	n->prev->next = newElemLL;
	n->prev = newElemLL;
}

bool findKey(List2W& l,int key, Element &elem){
	ElementLL* s = l.sentinel->next;
	while(s != l.sentinel && s->elem.key < key) s = s->next;
	if (s->elem.key == key){
		elem = s->elem;
		return true;
	}
	return false;
}

void removeAllKeys(List2W& l, int key){
	ElementLL* d = l.sentinel->next;
	while(d != l.sentinel && d->elem.key < key) d = d->next;
	if(d == l.sentinel || d->elem.key > key) return;
	while(d != l.sentinel && d->elem.key == key){
		ElementLL* k = d;
		d->prev->next = d->next;
		d->next->prev = d->prev;
		d = d->next;
		delete k;
	}
}

void showListFromHead(List2W& l){
	ElementLL* s = l.sentinel->next;
	while(s != l.sentinel){
		cout << s->elem.key << "(" << s->elem.value << "),";
		s = s->next;
	}
	cout << endl;
}

void showListFromTail(List2W& l){
	ElementLL* s = l.sentinel->prev;
	while(s != l.sentinel){
		cout << s->elem.key << "(" << s->elem.value << "),";
		s = s->prev;
	}
	cout << endl;
}

void clearList(List2W& l){
	while(l.sentinel != l.sentinel->next) deleteHead(l);
}

void addList(List2W& l1,List2W& l2){
	if (l1.sentinel == l2.sentinel || l2.sentinel->next == l2.sentinel) return;
	while(l2.sentinel->next != l2.sentinel){
		insertElem(l1,l2.sentinel->next->elem);
		deleteHead(l2);
	}
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

		// zero-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
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

		if(isCommand(command,"FK"))
		{
			Element elem;
			bool ret=findKey(list[currentL], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if(isCommand(command,"RK"))
		{
			removeAllKeys(list[currentL],value);
			continue;
		}

		if(isCommand(command,"CH"))
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key=value;
			elem.value=variable2;
			insertElem(list[currentL],elem);
			continue;
		}

		if(isCommand(command,"GO"))
		{
			list=new List2W[value];
			continue;
		}

		if(isCommand(command,"AD"))
		{
			addList(list[currentL],list[value]);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}

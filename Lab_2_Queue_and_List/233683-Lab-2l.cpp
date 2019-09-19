#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Element{
	int value;
	Element* next;
};

struct List{
	Element* hp;
};

void init(List& l){
	l.hp = NULL;
}

void insertHead(List& l, int x){
	Element* newhead = new Element();
	newhead->value = x;
	newhead->next = l.hp;
	l.hp = newhead;
}
 
bool deleteHead(List& l, int &oldHead){
	if (l.hp == NULL) return false;
	
	Element* k = l.hp;
	oldHead = l.hp->value;
	l.hp = l.hp->next;
	delete k;
	return true;
}

void insertTail(List& l, int x){
	//if is empty call insertHead
	if (l.hp == NULL) {
		insertHead(l,x);
		return;
	}
	//build new element
	Element* newtail = new Element;
	newtail->value = x;
	newtail->next = NULL;

	//look for the tail
	Element* oldtail = l.hp;
	while(oldtail->next != NULL) {
		oldtail = oldtail->next;
	}
	
	//connect new tail
	oldtail->next = newtail;
}

bool deleteTail(List& l, int &oldTail){
	if (l.hp == NULL) return false;
	
	Element* k;//element to be deleted
	Element* newtail = l.hp;//new tail, start at header
	
	if (l.hp->next == NULL) return deleteHead(l,oldTail); //only one element in the list
	
	//look for the newtail (prev elem to oldtail)
	while(newtail->next->next != NULL) {
		newtail = newtail->next;
	}
	oldTail = newtail->next->value;
	k = newtail->next;
	newtail->next = NULL;
	delete k;
	return true;
}

int findPosOfValue(List& l, int value){
		if (l.hp == NULL) return -1;
		
		Element* v = l.hp;
		int index = 0;
		while(v->next != NULL && v->value != value){
			v = v->next;
			index++;
		}
		if(v->value == value) return index;
		return -1;
}

bool deleteValue(List& l, int value){
		if (l.hp == NULL) return false;	//empty list
		
		if(l.hp->next == NULL){	//single element list
			Element* k = l.hp;
			if (l.hp->value != value) return false;
			else{
				l.hp = NULL;
				delete k;
				return true;
			}
		}
		
		//more than one element
		if(l.hp->value == value) {//head match
			Element* k = l.hp;
			l.hp = l.hp->next;
			delete k;
			return true;
		}
		
		Element* k = l.hp->next;
		Element* prev = l.hp;
		while(k->next != NULL && k->value != value) {
			prev = k;
			k = k->next;
		}
		if(k->value == value){
			if(k->next == NULL){//delete tail
				prev->next = NULL;
				delete k;
				return true;
			}
			//delete somewho in the middle
			prev->next = k->next;
			delete k;
			return true;
		}
		else return false;
}

bool atPosition(List& l, int pos, int &value){
	if (l.hp == NULL) return false; //empty list
	
	int index = 0;
	Element* p = l.hp;
	while(p->next != NULL && index != pos){
		p = p->next;
		index++;
	}
	if(index == pos) {
		value = p->value;
		return true;
	}
	return false;
}

void showListFromHead(List& l){
	Element* e = l.hp;
	while(e != NULL){
		cout << e->value << ",";
		e = e->next;
	}
	cout << endl;
}

void clearList(List& l){
	if (l.hp == NULL) return;
	
	Element* k;
	while(l.hp->next != NULL){
		k = l.hp;
		l.hp = l.hp->next;
		delete k;
	}
	k = l.hp;
	l.hp = NULL;
	delete k;
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
	List *list;
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
		if(isCommand(command,"DH"))
		{
			int retValue;
			bool retBool=deleteHead(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if(isCommand(command,"DT"))
		{
			int retValue;
			bool retBool=deleteTail(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"SH"))
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if(isCommand(command,"CL"))
		{
			clearList(list[currentL]);
			continue;
		}

		if(isCommand(command,"IN"))
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;
		
		if(isCommand(command,"FP"))
		{
			int ret;
			ret=findPosOfValue(list[currentL],value);
			cout << ret << endl;
			continue;
		}

		if(isCommand(command,"DV"))
		{
			showBool(deleteValue(list[currentL],value));
			continue;
		}


		if(isCommand(command,"AT"))
		{
			int retValue;
			bool retBool=atPosition(list[currentL],value,retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"CH"))
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IH"))
		{
			insertHead(list[currentL],value);
			continue;
		}

		if(isCommand(command,"IT"))
		{
			insertTail(list[currentL],value);
			continue;
		}

		if(isCommand(command,"GO"))
		{
			list=new List[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}

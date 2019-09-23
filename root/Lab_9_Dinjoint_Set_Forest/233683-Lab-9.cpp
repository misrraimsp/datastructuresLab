#include <iostream>
#include <string>
#include <sstream>

// DSF - disjoint sets forest

using namespace std;

// element of array
struct Element{
	int rank;
	int parent;
};

// DSF - disjoint sets forest
struct DSF{
	Element *arr;
	int size;
};

void init(DSF &dsf, int size){
	dsf.arr = new Element[size];
	dsf.size = size;
}

Element makeSet(int x){
	return {0, x};
}

void makeOneElementSets(DSF &dsf){
	for(int i = 0; i < dsf.size; i++){
		dsf.arr[i] = makeSet(i);
	}
}

int parent(DSF &dsf, int x){
	return dsf.arr[x].parent;
}

int find(DSF &dsf, int x){ // with path compression
	if(parent(dsf, x) != x) {
		dsf.arr[x].parent = find(dsf, parent(dsf, x));
	}
	return parent(dsf, x);
}

void link(DSF &dsf, int x1, int x2){
	if(dsf.arr[x1].rank < dsf.arr[x2].rank) {
		dsf.arr[x1].parent = x2;
	}
	else if (dsf.arr[x1].rank > dsf.arr[x2].rank) {
		dsf.arr[x2].parent = x1;
	}
	else {
		dsf.arr[x1].parent = x2;
		dsf.arr[x2].rank++;
	}
}

void makeUnion(DSF &dsf, int x1, int x2){
	int r1 = find(dsf, x1);
	int r2 = find(dsf, x2);
	if (r1 != r2) link(dsf, r1, r2);
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
	DSF *dsf=NULL;
	int currentF=0;
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

		if(isCommand(command,"MO"))
		{
			makeOneElementSets(dsf[currentF]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"IN"))
		{
			init(dsf[currentF],value);
			continue;
		}


		if(isCommand(command,"FD"))
		{
			cout << find(dsf[currentF],value) << endl;
			continue;
		}

		if(isCommand(command,"PA"))
		{
			cout << parent(dsf[currentF],value) << endl;
			continue;
		}

		if(isCommand(command,"UN"))
		{
			int value2;
			stream >> value2;
			makeUnion(dsf[currentF],value,value2);
			continue;
		}


		if(isCommand(command,"CH"))
		{
			currentF=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			dsf=new DSF[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;

	}
	return 0;
}

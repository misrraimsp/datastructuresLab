#include<iostream>
#include <string>
#include <sstream>

using namespace std;


struct Heap{
	int *arr;
	int size;
	int pos;
};

void init(Heap& h, int size){
	h.arr = new int[size];
	h.size = size;
	h.pos = 0;
}

void swap(int arr[], int index1, int index2) {
	int aux = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = aux;
}

void heapify(int arr[], int index, int limit) {
	int idxOfBigger = 2 * index + 1;
	if(idxOfBigger < limit) {
		if(idxOfBigger + 1 < limit && arr[idxOfBigger] < arr[idxOfBigger + 1]) idxOfBigger++;
		if(arr[index] < arr[idxOfBigger]) {
			swap(arr, index, idxOfBigger);
			heapify(arr, idxOfBigger, limit);
		}
	}
}

void heapAdjustment(Heap &h){
	for(int i = (h.pos - 1) / 2; i >= 0; i--) heapify(h.arr, i, h.pos);
}

void loadAndMakeHeap(Heap &h, int howMany){
	for(int i = 0; i < howMany; i++){
    	cin >> h.arr[i];
	}
	h.pos = howMany;
	//ajustar heap
	heapAdjustment(h);
}

void add(Heap &h, int value){
	if(h.pos == h.size) return; //	heap is full
	
	int insertPos = h.pos;
	int parentIndex = (insertPos - 1) / 2;
	
	while(insertPos != 0 && h.arr[parentIndex] < value){
		h.arr[insertPos] = h.arr[parentIndex];
		insertPos = parentIndex;
		parentIndex = (insertPos - 1) / 2;
	}
	h.arr[insertPos] = value;
	h.pos++;
}

void makeSorted(Heap& h){
	for(int i = h.pos - 1; i > 0; i--){
		swap(h.arr, i, 0);
		heapify(h.arr, 0, i);
	}
}

void show(Heap& h){
  for(int i=0;i<h.pos;i++)
  {
	  cout << h.arr[i] << ",";
  }
  cout << endl;
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
	Heap *heap;
	int currentH=0;
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
			show(heap[currentH]);
			continue;
		}

		if(isCommand(command,"MS")) //*
		{
			makeSorted(heap[currentH]);
			continue;
		}

		// read next argument, one int value
		stream >> value;
		
		if(isCommand(command,"IN")) //*
		{
			init(heap[currentH],value);
			continue;
		}

		if(isCommand(command,"LD")) 
		{
			loadAndMakeHeap(heap[currentH],value);
			continue;
		}

		if(isCommand(command,"AD")) 
		{
			add(heap[currentH],value);
			continue;
		}

		if(isCommand(command,"CH")) 
		{
			currentH=value;
			continue;
		}

		if(isCommand(command,"GO")) 
		{
			heap=new Heap[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void showArray(int array[], int size){
	for (int i = 0; i < size; i++){
		cout << array[i] << ",";
	}
	cout << endl;
}

void insertSort(int array[], int size){
	showArray(array,size);
	int i, insertPos, k, elem;
	for(i = size - 2; i >= 0; i--){
		elem = array[i];	//element to be added
		insertPos = size - 1;
		while(insertPos > i && array[insertPos] >= elem) insertPos--;	// search first lower
		for(k = i; k < insertPos; k++) array[k] = array[k + 1];	// shift elements
		array[insertPos]=elem;
		showArray(array,size);
	}
}

void bubbleSort(int array[], int size){
	int i, j, aux;
	for(i = 0; i <= size - 1; i++) {
		showArray(array,size);
		for(j = size - 1; j > i; j--) {
			if(array[j] < array[j - 1]) {
				aux = array[j];
				array[j] = array[j - 1];
				array[j - 1] = aux;
			}
		}
	}
}


void merge(int array[], int arrayAux[], int start1, int start2, int length){
	int index1 = start1;
	int index2 = start2;
	for (int i = start1; i < (start1 + length); i++){
		if(index1 < start2 && index2 < (start1 + length)){
			if(array[index1] <= array[index2]){
				arrayAux[i] = array[index1];
				index1++;
			}
			else{
				arrayAux[i] = array[index2];
				index2++;
			}
		}
		else if(index1 == start2){
			arrayAux[i] = array[index2];
			index2++;
		}
		else{
			arrayAux[i] = array[index1];
			index1++;
		}
	}
}

void mergeSortIter(int array[], int size){
	int* aux;
	int* arrayAux = new int[size];
	int startIndex1, startIndex2;
	int length = 1;
	
	showArray(array, size);
	if(size == 1) return;
	
	do {
		startIndex1 = 0;
		startIndex2 = length;
		length = length * 2;
		while (startIndex2 < size){
			if (startIndex1 + length <= size){
				merge(array, arrayAux, startIndex1, startIndex2, length);
				startIndex1 = startIndex1 + length;
				startIndex2 = startIndex2 + length;
			}
			else{
				merge(array, arrayAux, startIndex1, startIndex2, size - startIndex1);
				startIndex1 = size;
				startIndex2 = size;
			}
		}
		for(int i = startIndex1; i < size; i++) arrayAux[i] = array[i];
		//	swap pointers to first element
		aux = arrayAux;
		arrayAux = array;
		array = aux;
		//	show current state
		showArray(array, size);
	} while(length * 2 <= size);
	//	if size is not a power of 2, then length < size and
	//	it is necessary to merge last two sorted, different sized, arrays.
	//	second array start at index equal to current length value
	if(length < size){
		merge(array, arrayAux, 0, length, size);
		//	swap pointers to first element
		aux = arrayAux;
		arrayAux = array;
		array = aux;
		//	show final state
		showArray(array, size);
	}
	//free memory
	delete arrayAux;
}

int* loadArray(int size){
	int* array = new int[size];
	for(int i = 0; i < size; i++){
    	cin >> array[i];
	}
	return array;
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	int size=0;
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

		// read next argument, one int size
		stream >> size;

		// one-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if(isCommand(command,"IS")) //*
		{
			int *arr=loadArray(size);
			//cout << "insertSort" << endl;
			//showArray(arr,size);
			insertSort(arr,size);
			continue;
		}

		if(isCommand(command,"BS")) //*
		{
			int *arr=loadArray(size);
			//cout << "bubbleSort" << endl;
			//showArray(arr,size);
			bubbleSort(arr,size);
			continue;
		}

		if(isCommand(command,"MI")) //*
		{
			int *arr=loadArray(size);
			//cout << "mergeSortIter" << endl;
			//showArray(arr,size);
			mergeSortIter(arr,size);
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}

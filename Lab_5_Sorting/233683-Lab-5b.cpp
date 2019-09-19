#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

# define MAX 100

using namespace std;

void showArray(int array[], int size){
	for (int i = 0; i < size; i++){
		cout << array[i] << ",";
	}
	cout << endl;
}

void insertSort(int array[], int size){
	int i, insertPos, k, elem;
	for(i = size - 2; i >= 0; i--){
		elem = array[i];	//element to be added
		insertPos = size - 1;
		while(insertPos > i && array[insertPos] >= elem) insertPos--;	// search first lower
		for(k = i; k < insertPos; k++) array[k] = array[k + 1];	// shift elements
		array[insertPos]=elem;
		//showArray(array,size);
	}
}

void bubbleSort(int array[], int size){
	int i, j, aux;
	for(i = 0; i <= size - 1; i++) {
		for(j = size - 1; j > i; j--) {
			if(array[j] < array[j - 1]) {
				aux = array[j];
				array[j] = array[j - 1];
				array[j - 1] = aux;
			}
			//showArray(array,size);
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
		//showArray(array, size);
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
	}
	//	show final state
	//showArray(array, size);
}



int* loadArray(int size){
	int* array = new int[size];
	srand(time(0)); // use current time as seed for random generator
	for(int i = 0; i < size; i++){
    	array[i] = rand() % MAX + 1;
	}
	return array;
}




int main(){
	int size = 125000;
	int* arr;
	
	arr = loadArray(size);
	clock_t beginIS = clock();
	insertSort(arr, size);
	clock_t endIS = clock();
	double elapsed_secsIS = endIS - beginIS;
	//double elapsed_secsIS = double(endIS - beginIS) / CLOCKS_PER_SEC;
	cout << "InsertSort: " << elapsed_secsIS << endl;
	
	arr = loadArray(size);
	clock_t beginBS = clock();
	bubbleSort(arr, size);
	clock_t endBS = clock();
	double elapsed_secsBS = endBS - beginBS;
	//double elapsed_secsBS = double(endBS - beginBS) / CLOCKS_PER_SEC;
	cout << "BubbleSort: " << elapsed_secsBS << endl;
	
	arr = loadArray(size);
	clock_t beginMS = clock();
	mergeSortIter(arr, size);
	clock_t endMS = clock();
	double elapsed_secsMS = endMS - beginMS;
	//double elapsed_secsMS = double(endMS - beginMS) / CLOCKS_PER_SEC;
	cout << "MergeSortIter: " << elapsed_secsMS << endl;
	
	return 0;
}

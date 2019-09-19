#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <array>
#include <map>
#include <unordered_map>
using namespace std;



// 	PROBLEM PARAMETERS
//////////////////////////////////////////////////////////////////////////////////////////////////	
const string FILE_NAME = "War and Peace.txt";													//
const char OPTION = 'c'; /* (a) BST, (b) Balanced BST, (c) Hash	*/								//
const int SIZE = 100;																			//
//////////////////////////////////////////////////////////////////////////////////////////////////



class TokenSource{
	private:
		ifstream file;
	public:
		TokenSource(string);	//Constructor
		string getNextToken();
};

TokenSource::TokenSource(string filename){
	file.open(filename.c_str());
}

string TokenSource::getNextToken(){
	string token;
	char c;
	//	get first valid char
	do {
		c = tolower(file.get());
		if(c == EOF){
			file.close();
			return "EOF";	
		}
	} while(c < 'a' || c > 'z');
	//	get following valid chars
	do {
		token.append(1, c);
		c = tolower(file.get());
	} while(c >= 'a' && c <= 'z');
	if (c == EOF) file.close();
	return token;
}

struct Element{
	string key;
	int freq;
};

struct Node{
	Element elem;
	Node* p;
	Node* lc;
	Node* rc;
};

struct BST{
	Node* root;
};

void init(BST &tree){
	tree.root = NULL;
}

void insert(Node* node, Node* newN){
	//	left subtree
	if(newN->elem.key < node->elem.key){
		if(node->lc == NULL){
			node->lc = newN;
			newN->p = node;
			return;
		}
		return insert(node->lc, newN);
	}
	//	right subtree
	if(newN->elem.key > node->elem.key){
		if(node->rc == NULL){
			node->rc = newN;
			newN->p = node;
			return;
		}
		return insert(node->rc, newN);
	}
	//	node already exists
	node->elem.freq = newN->elem.freq;
	return;
}

void insert(BST &tree, Element e){
	//	build new node
	Node* n = new Node;
	n->elem = e;
	n->p = NULL;
	n->lc = NULL;
	n->rc = NULL;
	//	empty tree case
	if (tree.root == NULL){
		tree.root = n;
		return;	
	}
	//	non empty tree: recursive case	
	return insert(tree.root, n);
}

Node* findNode(Node* node, string key){
	if (node == NULL) return NULL;
	if (key < node->elem.key) return findNode(node->lc, key);
	if (key > node->elem.key) return findNode(node->rc, key);
	return node;
}

bool findKey(BST &tree, string key, Element &elem){
	Node* n = findNode(tree.root, key);
	if(n != NULL){
		elem = n->elem;
		return true;
	}
	return false;
}

class Elite{
	private:
		array<Element,SIZE> top;
		int threshold;
		int size;
		bool full;
		void insert(Element&);
	public:
		Elite();
		void populate(Node*);
		void populate(map<string,int>&);
		void populate(unordered_map<string,int>&);
		void print();
};

Elite::Elite(){
	top.fill({"#", 1});
	threshold = 1;
	size = 0;
	full = false;
}

void Elite::insert(Element &e){
	if(full){
		if(e.freq <= threshold) return;
		int index = top.size() - 1;
		while(index >= 0 && top[index].freq < e.freq) index--;
		for (int i = top.size() - 1; i > index + 1; i--) top[i] = top[i - 1];
		top[index + 1] = {e.key, e.freq};
		threshold = top.back().freq;
	}
	else{
		if(e.freq <= threshold) top[size] = {e.key, e.freq};
		else{
			int index = size - 1;
			while(index >= 0 && top[index].freq < e.freq) index--;
			for (int i = size; i > index + 1; i--) top[i] = top[i - 1];
			top[index + 1] = {e.key, e.freq};
		}
		size++;
		full = (size == top.size());
	}
}

void Elite::populate(Node* n){
	if(n == NULL) return;
	populate(n->lc);
	insert(n->elem);
	populate(n->rc);
}

void Elite::populate(map<string,int> &Btree){
	Element e;
	for (map<string,int>::iterator it = Btree.begin(); it != Btree.end(); ++it){
		e = {it->first, it->second};
		insert(e);
	}
}

void Elite::populate(unordered_map<string,int> &Htable){
	Element e;
	for (unordered_map<string,int>::iterator it = Htable.begin(); it != Htable.end(); ++it){
		e = {it->first, it->second};
		insert(e);
	}
}

void Elite::print(){
	cout << "FREQ" << "\t" << "KEY" << endl;
	for ( Element &e : top) { 
		cout << e.freq << "\t" << e.key << endl;
	}
}

void count_A(BST &tree, TokenSource &ts){
	Element e;
	string key = ts.getNextToken();
	while (key != "EOF"){
		if (findKey(tree, key, e)) e.freq++;
		else e = {key, 1};
		insert(tree, e);
		key = ts.getNextToken();
	}
}

void count_B(map<string,int> &Btree, TokenSource &ts){
	map<string,int>::iterator it;
	string key = ts.getNextToken();
	while (key != "EOF"){
		it = Btree.find(key);
		if(it != Btree.end()) Btree[key] = it->second + 1;
		else Btree[key] = 1;
		key = ts.getNextToken();
	}
}

void count_C(unordered_map<string,int> &Htable, TokenSource &ts){
	unordered_map<string,int>::iterator it;
	string key = ts.getNextToken();
	while (key != "EOF"){
		it = Htable.find(key);
		if(it != Htable.end()) Htable[key] = it->second + 1;
		else Htable[key] = 1;
		key = ts.getNextToken();
	}
}

int main () {
	clock_t t;
	TokenSource ts(FILE_NAME);
	Elite elite;
	if (OPTION == 'a'){
		BST tree;
		init(tree);
		t = clock();
  		count_A(tree, ts);
		t = clock() - t;
		cout << "Done!" << endl;
		elite.populate(tree.root);
	}
	else if (OPTION == 'b'){
		map<string,int> Btree;
		t = clock();
  		count_B(Btree, ts);
		t = clock() - t;
		cout << "Done!" << endl;
		elite.populate(Btree);
	}
	else if (OPTION == 'c'){
		unordered_map<string, int> Htable;
		t = clock();
  		count_C(Htable, ts);
		t = clock() - t;
		cout << "Done!" << endl;
		elite.populate(Htable);
	}
	else{
		cout << "Select a valid option: (a) BST, (b) Balanced BST, (c) Hash" << endl;
		return 0;
	}
	elite.print();
	printf ("Counting took %d clicks (%f seconds).\n", t, ((float)t)/CLOCKS_PER_SEC);
	return 0;
}

#include <iostream>
#include <string>
#include <sstream>
using namespace std;


struct Element{
	int key;
	int value;
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

void init(BST& tree){
	tree.root = NULL;
}


//	INSERT
/////////////////////////////////////////////////////////////////////////////////////////////
bool insertElem(Node* np, Node* n){
	//	left subtree
	if(n->elem.key < np->elem.key){
		if(np->lc == NULL){
			np->lc = n;
			n->p = np;
			return true;
		}
		return insertElem(np->lc, n);
	}
	
	//	right subtree
	if(n->elem.key > np->elem.key){
		if(np->rc == NULL){
			np->rc = n;
			n->p = np;
			return true;
		}
		return insertElem(np->rc, n);
	}
	
	//	key already exists
	return false;
}

bool insertElem(BST& tree, Element e){
	//	build new node
	Node* n = new Node;
	n->elem = e;
	n->p = NULL;
	n->lc = NULL;
	n->rc = NULL;
	
	//	empty tree case
	if (tree.root == NULL){
		tree.root = n;
		return true;	
	}
	
	//	non empty tree: recursive case	
	return insertElem(tree.root, n);
}


//	SHOW IN-ORDER
/////////////////////////////////////////////////////////////////////////////////////////////
void showInorder(Node* n){
	//	base case
	if(n == NULL) return;
	
	//	recursive case
	showInorder(n->lc);
	cout << n->elem.key << "(" << n->elem.value << ")" << ",";
	showInorder(n->rc);
}

void showInorder(BST& tree){
	showInorder(tree.root);
	cout << endl;
}

//	SHOW PRE-ORDER
/////////////////////////////////////////////////////////////////////////////////////////////
void showPreorder(Node* n){
	//	base case
	if(n == NULL) return;
	
	//	recursive case
	cout << n->elem.key << "(" << n->elem.value << ")" << ",";
	showPreorder(n->lc);
	showPreorder(n->rc);
}

void showPreorder(BST& tree){
	showPreorder(tree.root);
	cout << endl;
}

//	SHOW POST-ORDER
/////////////////////////////////////////////////////////////////////////////////////////////
void showPostorder(Node* n){
	//	base case
	if(n == NULL) return;
	
	//	recursive case
	showPostorder(n->lc);
	showPostorder(n->rc);
	cout << n->elem.key << "(" << n->elem.value << ")" << ",";
}

void showPostorder(BST& tree){
	showPostorder(tree.root);
	cout << endl;
}

//	FIND KEY
/////////////////////////////////////////////////////////////////////////////////////////////
Node* findNode(Node* node, int key){
	if (node == NULL) return NULL;
	if (key < node->elem.key) return findNode(node->lc, key);
	if (key > node->elem.key) return findNode(node->rc, key);
	return node;
}

bool findKey(BST& tree, int key, Element& elem){
	Node* n = findNode(tree.root, key);
	if(n != NULL){
		elem = n->elem;
		return true;
	}
	return false;
}

//	NUMBER OF NODES
/////////////////////////////////////////////////////////////////////////////////////////////
int numberOfNodes(Node* node){
	if (node == NULL) return 0;
	return 1 + numberOfNodes(node->lc) + numberOfNodes(node->rc);
}

int numberOfNodes(BST& tree){
	return numberOfNodes(tree.root);
}

//	REMOVE
/////////////////////////////////////////////////////////////////////////////////////////////
Node* minimalNode(Node* node){
	Node* min = node;
	while(min->lc != NULL){
		min = min->lc;
	}
	return min;
}

//	assuming node has no children
void delete0(Node* node){
	if(node->p == NULL){
		delete node;
		return;
	}
	if(node->p->lc == node) node->p->lc = NULL;
	else node->p->rc = NULL;
	delete node;
}

//	assuming node has 1 child
void delete1(Node* node){
	Node* c;
	if (node->lc != NULL) c = node->lc;
	else c = node->rc;
	
	//if(node->p == NULL)
	if(node->p->lc == node) node->p->lc = c;
	else node->p->rc = c;
	c->p = node->p;
	delete node;
}

//	assuming node has 2 children
void delete2(Node* node){
	Node* suc = minimalNode(node->rc);
	node->elem = suc->elem;
	if (suc->rc != NULL) delete1(suc);
	else delete0(suc);
}

bool removeKey(BST& tree, int key, Element& elem){
	Node* node = findNode(tree.root, key);
	if (node == NULL) return false;
	elem = node->elem;
	if (node->lc == NULL && node->rc == NULL){
		if (numberOfNodes(tree) == 1){
			delete0(node);
			tree.root = NULL;
		}
		else delete0(node);
		return true;	
	}
	if (node->lc != NULL && node->rc != NULL){
		delete2(node);
		return true;	
	}
	if (node == tree.root){
		if(node->lc != NULL) tree.root = node->lc;
		else tree.root = node->rc;
		delete node;
		return true;
	}
	delete1(node);
	return true;
}

void clear(Node* node){
	if(node == NULL) return;
	
	clear(node->lc);
	clear(node->rc);
	delete0(node);
	
}

void clear(BST& tree){
	clear(tree.root);
	tree.root = NULL;
}


//	HEIGHT
/////////////////////////////////////////////////////////////////////////////////////////////
int height(Node* node){
	if (node == NULL) return 0;
	int hl = height(node->lc);
	int hr = height(node->rc);
	if (hl > hr) return 1 + hl;
	return 1 + hr;
}

int height(BST& tree){
	return height(tree.root);
}





int functionA(BST & tree){
	return -1;
}

int functionB(BST & tree, int key){
	return -1;
}

bool functionC(BST & tree, int key, Element &elem){
	return false;
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
	BST *tree;
	int currentT=0;
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

		if(isCommand(command,"SI"))
		{
			showInorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"SP"))
		{
			showPreorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"SQ"))
		{
			showPostorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"CL"))
		{
			clear(tree[currentT]);
			continue;
		}

		if(isCommand(command,"IN"))
		{
			init(tree[currentT]);
			continue;
		}

		if(isCommand(command,"NN"))
		{
			cout << numberOfNodes(tree[currentT]) << endl;
			continue;
		}

		if(isCommand(command,"HE"))
		{
			cout << height(tree[currentT]) << endl;
			continue;
		}

		if(isCommand(command,"FA"))
		{
			cout << functionA(tree[currentT]) << endl;
			continue;
		}

		// read next argument, one int value
		stream >> value;


		if(isCommand(command,"IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key=value;
			elem.value=variable2;
			showBool(insertElem(tree[currentT],elem));
			continue;
		}

		if(isCommand(command,"FK"))
		{
			Element elem;
			bool ret=findKey(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if(isCommand(command,"RK"))
		{
			Element elem;
			bool ret=removeKey(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}


		if(isCommand(command,"CH"))
		{
			currentT=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			tree=new BST[value];
			continue;
		}

		if(isCommand(command,"FB"))
		{
			cout << functionB(tree[currentT],value) << endl;
			continue;
		}

		if(isCommand(command,"FC"))
		{
			Element elem;
			bool ret=functionC(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		cout << "wrong argument in test: " << command << endl;

	}
	return 0;
}

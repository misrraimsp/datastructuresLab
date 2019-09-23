#include <iostream>
#include <string.h>
#include <sstream>
#include <cstdlib>

using namespace std;

struct Node{
	int vertice;
	double weight;
	Node* next;
};

struct List{
	Node* h;
};

struct Graph{
	int numberOfV;
	List* lists;
};


//code from stackoverflow website
 double string_to_double( const std::string& s )
 {
   std::istringstream i(s);
   double x;
   if (!(i >> x))
     return 0;
   return x;
 }
//

void insert(List &list, Node* newNode){
	//empty list
	if (list.h == NULL) {
		list.h = newNode;
		return;
	}
	//head case
	if (list.h->vertice > newNode->vertice) {
		newNode->next = list.h;
		list.h = newNode;
		return;
	}
	if (list.h->vertice == newNode->vertice) { //only update weight
		list.h->weight = newNode->weight;
		return;
	}
	//general case
	Node* prev = list.h;
	Node* next = list.h->next;
	while(next != NULL && next->vertice < newNode->vertice) {
		prev = next;
		next = next->next;
	}
	if (next == NULL){ //insert as tail
		prev->next = newNode;
		return;
	}
	if (next->vertice == newNode->vertice) { //only update weight
		next->weight = newNode->weight;
		return;
	}
	newNode->next = next;
	prev->next = newNode;
}

void insertEdge(Graph &g, int u, int v, double weight){
	if (u >= g.numberOfV || v >= g.numberOfV) return;
	Node* node = new Node();
	node->vertice = v;
	node->weight = weight;
	node->next = NULL;
	//cout << "ok2" << endl;
	insert(g.lists[u], node);
}

void loadGraph(Graph &g, int n, int m){
	string line;
	int v1, v2;
	double w;
	//initialize the array of lists
	g.numberOfV = n;
	g.lists = new List[n];
	for (int i = 0; i < n; i++) g.lists[i].h = NULL;
	//populate the lists with m vertices
	for (int j = 0; j < m; j++){
		getline(cin, line);
  		v1 = atoi(line.substr(0, 1).c_str());
  		v2 = atoi(line.substr(2, 1).c_str());
		w = string_to_double(line.substr(4));
		//cout << "ok1" << endl;
		insertEdge(g, v1, v2, w);
	}
}

bool find(List list, int v, double &weight){
	Node* n = list.h;
	while (n != NULL && n->vertice != v) n = n->next;
	if (n == NULL) return false;
	weight = n->weight;
	return true;
}

bool findEdge(Graph &g, int u, int v, double &weight){
	if (u == v || u >= g.numberOfV || v >= g.numberOfV) return false;
	return find(g.lists[u], v, weight);
}

void showAsMatrix(Graph &g){
	double w;
	for(int i = 0; i < g.numberOfV; i++){
		for (int j = 0; j < g.numberOfV; j++){
			if (i == j) cout << 0 << ",";
			else if (findEdge(g, i, j, w)) cout << w << ",";
			else cout << "-,";
		}
		cout << endl;
	}
}

void showAsArrayOfLists(Graph &g){
	double w;
	for(int i = 0; i < g.numberOfV; i++){
		cout << i << ":";
		for (int j = 0; j < g.numberOfV; j++){
			if (findEdge(g, i, j, w)) cout << j << "(" << w << ")" << ",";
		}
		cout << endl;
	}
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}


int main(){
	string line;
	string command;
	Graph *graph;
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
		// zero-argument command
		if(isCommand(command,"SM"))
		{
			showAsMatrix(graph[currentT]);
			continue;
		}

		if(isCommand(command,"SA"))
		{
			showAsArrayOfLists(graph[currentT]);
			continue;
		}


		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"LG"))
		{
			int m;
			stream >> m;
			loadGraph(graph[currentT],value,m);
			continue;
		}

		if(isCommand(command,"IE"))
		{
			int v;
			double w;
			stream >> v >> w;
			insertEdge(graph[currentT],value,v,w);
			continue;
		}

		if(isCommand(command,"FE"))
		{
			int v;
			stream >> v;
			double w;
			bool ret=findEdge(graph[currentT],value,v,w);

			if(ret)
				cout << w << endl;
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
			graph=new Graph[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}

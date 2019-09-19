#include <iostream>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <queue>

using namespace std;

#define INFINITY 10000000

struct Edge{
	double weight;
	int destIndex;
	Edge* nextEdge;
};

struct Vertex{
	int id;
	int colour; //'0' white, '1' grey, '2' black
	double distance;
	int preIndex;
	Edge* firstEdge;
};

struct Graph{
	Vertex* vertices;
	int numberOfV;
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

void insert(Vertex &vertex, Edge* newEdge){
	//empty list
	if (vertex.firstEdge == NULL) {
		vertex.firstEdge = newEdge;
		return;
	}
	//head case
	if (vertex.firstEdge->destIndex > newEdge->destIndex) {
		newEdge->nextEdge = vertex.firstEdge;
		vertex.firstEdge = newEdge;
		return;
	}
	if (vertex.firstEdge->destIndex == newEdge->destIndex) { //only update weight
		vertex.firstEdge->weight = newEdge->weight;
		return;
	}
	//general case
	Edge* prev = vertex.firstEdge;
	Edge* next = vertex.firstEdge->nextEdge;
	while(next != NULL && next->destIndex < newEdge->destIndex) {
		prev = next;
		next = next->nextEdge;
	}
	if (next == NULL){ //insert as tail
		prev->nextEdge = newEdge;
		return;
	}
	if (next->destIndex == newEdge->destIndex) { //only update weight
		next->weight = newEdge->weight;
		return;
	}
	newEdge->nextEdge = next;
	prev->nextEdge = newEdge;
}

void insertEdge(Graph &g, int u, int v, double weight){
	if (u >= g.numberOfV || v >= g.numberOfV) return;
	Edge* edge = new Edge();
	edge->destIndex = v;
	edge->weight = weight;
	edge->nextEdge = NULL;
	insert(g.vertices[u], edge);
}

void loadGraph(Graph &g, int n, int m){
	string line;
	int v1, v2;
	double w;
	//initialize vertices
	g.numberOfV = n;
	g.vertices = new Vertex[n];
	for (int i = 0; i < n; i++) {
		g.vertices[i].id = i;
		g.vertices[i].distance = -1;
		g.vertices[i].colour = -1;
		g.vertices[i].preIndex = -1;
		g.vertices[i].firstEdge = NULL;
	}
	//populate the lists with m vertices
	for (int j = 0; j < m; j++){
		getline(cin, line);
  		v1 = atoi(line.substr(0, 1).c_str());
  		v2 = atoi(line.substr(2, 1).c_str());
		w = string_to_double(line.substr(4));
		insertEdge(g, v1, v2, w);
	}
}

bool find(Vertex vertex, int dest, double &weight){
	Edge* e = vertex.firstEdge;
	while (e != NULL && e->destIndex != dest) e = e->nextEdge;
	if (e == NULL) return false;
	weight = e->weight;
	return true;
}

bool findEdge(Graph &g, int u, int v, double &weight){
	if (u == v || u >= g.numberOfV || v >= g.numberOfV) return false;
	return find(g.vertices[u], v, weight);
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

void BFS(Graph &g, int s){
	if (s < 0 || s >= g.numberOfV) return;
	queue<Vertex> q;
	int index1, index2;
	Edge* e;
	//set initial conditions
	for (int i = 0; i < g.numberOfV; i++){
		if (g.vertices[i].id == s){
			g.vertices[i].distance = 0;
			g.vertices[i].colour = 1; // grey
		}
		else {
			g.vertices[i].distance = INFINITY;
			g.vertices[i].colour = 0; // white
		}
		g.vertices[i].preIndex = -1;
	}
	q.push(g.vertices[s]);
	//walk
	while (!q.empty()) {
		index1 = q.front().id;
		q.pop();
		e = g.vertices[index1].firstEdge;
		//go through all adjacent vertices
		while (e != NULL){
			index2 = g.vertices[e->destIndex].id;
			if (g.vertices[index2].colour == 0){ //if white (not visited)
				g.vertices[index2].colour = 1;//grey
				g.vertices[index2].distance = g.vertices[index1].distance + 1;
				g.vertices[index2].preIndex = index1;
				q.push(g.vertices[index2]);
			}
			e = e->nextEdge;
		}
		g.vertices[index1].colour = 2; // black
		cout << index1 << ",";
	}
	cout << endl;
}

void DFS_Visit(Graph &g, int id){
	Edge* e;
	cout << id << ",";
	e = g.vertices[id].firstEdge;
	while (e != NULL){
		if (g.vertices[e->destIndex].colour == 0){ //white
			g.vertices[e->destIndex].colour = 1; //get grey
			g.vertices[e->destIndex].preIndex = id;
			DFS_Visit(g, e->destIndex);
		}
		e = e->nextEdge;
	}
	g.vertices[id].colour = 2; //get black
}

void DFS(Graph &g, int s){
	if (s < 0 || s >= g.numberOfV) return;
	//set initial conditions
	for (int i = 0; i < g.numberOfV; i++){
		g.vertices[i].colour = 0; //white
		g.vertices[i].preIndex = -1;
	}
	//walk
	g.vertices[s].colour = 1; //get grey
	DFS_Visit(g, s);
	cout << endl;
}

int* SSSP(Graph &g, int s){
	if (s < 0 || s >= g.numberOfV) return NULL;
	//all vertex distance=infinity, colour=0 (white)
	for (int i = 0; i < g.numberOfV; i++){
		g.vertices[i].distance = INFINITY;
		g.vertices[i].colour = 0;
	}
	//initial conditions
	g.vertices[s].distance = 0;
	g.vertices[s].colour = 2;
	int numberOfDistances = 1;
	Edge* e = g.vertices[s].firstEdge;
	while (e != NULL){
		g.vertices[e->destIndex].distance = e->weight;
		e = e->nextEdge;
	}
	//loop
	double min;
	int index;
	while (numberOfDistances < g.numberOfV){
		//look for min
		min = INFINITY;
		for (int i = 0; i < g.numberOfV; i++){
			if (g.vertices[i].colour == 0) {
				if (g.vertices[i].distance < min) {
					index = i;
					min = g.vertices[i].distance;
				}
			}
		}
		g.vertices[index].colour = 2;
		numberOfDistances++;
		//update distances
		e = g.vertices[index].firstEdge;
		while (e != NULL){
			if (g.vertices[e->destIndex].colour == 0) {
				double newDist = g.vertices[index].distance + e->weight;
				double oldDist = g.vertices[e->destIndex].distance;
				if (newDist < oldDist) g.vertices[e->destIndex].distance = newDist;
			}
			e = e->nextEdge;
		}
	}
	//build output
	int* d = new int[g.numberOfV];
	for (int i = 0; i < g.numberOfV; i++){
		d[i] = g.vertices[i].distance;
	}
	return d;
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
		
		if(isCommand(command,"BF"))
		{
			BFS(graph[currentT], value);
			continue;
		}
		
		if(isCommand(command,"DF"))
		{
			DFS(graph[currentT], value);
			continue;
		}
		
		if(isCommand(command,"SS"))
		{
			int* distances = SSSP(graph[currentT], value);
			for (int i = 0; i < graph[currentT].numberOfV; i++){
				cout << i << "(" << distances[i] << ")" << endl;
			}
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}

#include <iostream>
#include <string.h>
#include <sstream>
#include <cstdlib>

using namespace std;

#define INFINITY 10000000

struct Graph{
	int numberOfV;
	int numberOfE;
	double **data;
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

void insertEdge(Graph &g, int u, int v, double weight){
	if (u >= g.numberOfV || v >= g.numberOfV) return;
	g.data[u][v] = weight;
	g.numberOfE++;
}

void loadGraph(Graph &g, int n, int m){
	string line;
	int v1, v2;
	double w;
	//initialize the matrix
	g.data = new double*[n];
    for (int i = 0; i < n; i++) {
        g.data[i] = new double[n];
    }
	g.numberOfV = n;
	g.numberOfE = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (i == j) g.data[i][j] = 0;
			else g.data[i][j] = INFINITY;
		}
	}
	//populate the matrix with m vertices
	for (int i = 0; i < m; i++){
		getline(cin, line);
  		v1 = atoi(line.substr(0, 1).c_str());
  		v2 = atoi(line.substr(2, 1).c_str());
		w = string_to_double(line.substr(4));
		insertEdge(g, v1, v2, w);
	}
}

bool findEdge(Graph &g, int u, int v, double &weight){
	if (u != v && g.data[u][v] != INFINITY){
		weight = g.data[u][v];
		return true;
	}
	return false;
}

void showAsMatrix(Graph &g){
	for(int i = 0; i < g.numberOfV; i++){
		for (int j = 0; j < g.numberOfV; j++){
			if (g.data[i][j] != INFINITY) cout << g.data[i][j] << ",";
			else cout << "-,";
		}
		cout << endl;
	}
}

void showAsArrayOfLists(Graph &g){
	for(int i = 0; i < g.numberOfV; i++){
		cout << i << ":";
		for (int j = 0; j < g.numberOfV; j++){
			if (i != j && g.data[i][j] != INFINITY) cout << j << "(" << g.data[i][j] << ")" << ",";
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

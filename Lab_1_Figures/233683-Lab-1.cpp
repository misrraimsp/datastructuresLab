#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;

// help function
void drawStr(int n, char c) {
	for (int i = 1; i <= n; i++) {
		cout << c;
	}
}

// size from 2 to 20
void drawTriangle(int size){
	for (int i = 1;  i <= size; i++) {
        drawStr(i, 'X');
        cout << endl;
	}
}

// size from 2 to 20
void drawSquare(int size){
   
    int aux = size - 2;
    
    //first line
    drawStr(size, 'X');
    cout << endl;
    
    //middle lines
    for (int i = 1; i <= aux; i++) {
        drawStr(1, 'X');
        drawStr(aux, ' ');
        drawStr(1, 'X');
        cout << endl;
    }

    //last line
    drawStr(size, 'X');
    cout << endl;
}

void drawPyramid(int size, int offset){
    //initial setup
    int numX = 1;
    int numSpace = offset + size - 1;
    
    //loop
    for (int i = 1; i <= size; i++) {
        drawStr(numSpace, ' ');
        drawStr(numX, 'X');
        cout << endl;
        numX = numX + 2;
        numSpace = numSpace - 1;
    }
}

// size from 1 to 20
void drawPyramid(int size){
    drawPyramid(size, 0);
}

// size from 1 to 20
void drawChristmasTree(int size){
    for (int i = 1; i <= size; i++) {
        drawPyramid(i, size - i);
    }
}

// size from 2 to 20
void drawFigureX(int size){
}

// size from 2 to 20
void drawFigureY(int size){
}

// size from 3 to 20
void drawFigureZ(int size){
}

// size from 2 to 20
void drawFigureW(int size){
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line; 
	string command;
	int value;
	cout << "START" << endl;
	while(true){
//		cin.getline(line, MAXLINE);
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

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"TR"))
		{
			drawTriangle(value);
			continue;
		}
		if(isCommand(command,"SQ"))
		{
			drawSquare(value);
			continue;
		}
		if(isCommand(command,"PY"))
		{
			drawPyramid(value);
			continue;
		}
		if(isCommand(command,"CT"))
		{
			drawChristmasTree(value);
			continue;
		}
		if(isCommand(command,"FX"))
		{
			drawFigureX(value);
			continue;
		}
		if(isCommand(command,"FY"))
		{
			drawFigureY(value);
			continue;
		}
		if(isCommand(command,"FZ"))
		{
			drawFigureZ(value);
			continue;
		}
		if(isCommand(command,"FW"))
		{
			drawFigureW(value);
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}
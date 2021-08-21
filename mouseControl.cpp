#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;

pair<int,int> gridPos[4][4];
/*{
	{{268,416},{350,416},{435,416},{521,416}},
	{{268,504},{350,504},{435,504},{521,504}},
	{{268,589},{350,589},{435,589},{521,589}},
	{{268,676},{350,676},{435,676},{521,676}}
};*/

INPUT Input;
const int bridge = 30, nextWord = 55; 
const int ROWS = 4, COLS = 4;

void leftDown(){
	Input={0};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1,&Input,sizeof(INPUT));
}

void leftUp(){	
	::ZeroMemory(&Input,sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1,&Input,sizeof(INPUT));
}

void getGridPos(){
	POINT p1, p2;
	int wait;
	cout << "Enter 0 when mouse is over top left cell\n";
	cin >> wait;
	GetCursorPos(&p1);
	cout << "Enter 0 when mouse is over bottom right cell\n";
	cin >> wait;
	GetCursorPos(&p2);
	int dx = (p2.x - p1.x) / (COLS-1);
	int dy = (p2.y - p1.y) / (ROWS-1);
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++)
			gridPos[i][j] = {p1.x + j*dx, p1.y + i*dy};
	}
}

void inputWord(vector<pair<int,int> >& moves){
	pair <int,int> p = gridPos[moves[0].first][moves[0].second]; 
	SetCursorPos(p.first, p.second);
	leftDown();
	Sleep(bridge);
	for(int i = 1; i < (int)moves.size(); i++){
		p = gridPos[moves[i].first][moves[i].second];
		SetCursorPos(p.first, p.second);
		Sleep(bridge);
	}
	leftUp();
	Sleep(nextWord);
}


#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;

pair<int,int> gridPos[4][4];

INPUT Input;

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

const int bridge = 30;
const int nextWord = 120; 

void getPosition(){
	int wait;
	cout << "Enter 0 when you have alligned upper left corner\n";
	cin >> wait;
	POINT p1;
	GetCursorPos(&p1);
	cout << "Enter 0 when you have alligned bottom right corner of top left cell\n";
	cin >> wait;
	POINT p2;
	GetCursorPos(&p2);
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	int x0 = (p1.x + p2.x)/2;
	int y0 = (p1.y + p2.y)/2;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			gridPos[i][j] = {x0 + i*dx, y0 + j*dy};
		}
	}
	cout << "Calculated Position\n";
}

void inputWord(vector<pair<int,int> >& moves){
	pair <int,int> p = gridPos[moves[0].first][moves[0].second]; 
	SetCursorPos(p.first, p.second+14);
	leftDown();
	Sleep(bridge);
	for(int i = 1; i < (int)moves.size(); i++){
		p = gridPos[moves[i].first][moves[i].second];
		SetCursorPos(p.first, p.second+14);
		Sleep(bridge);
	}
	leftUp();
	Sleep(nextWord);
}



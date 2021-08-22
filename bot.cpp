#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "encoder.cpp"
#include "mouseControl.cpp"
using namespace std;

struct Node{
	unordered_map <int,int> child; 
	bool isWord;
};

int cap = 1000;
int curNode = 1;
Node T[2000000];
int grid[4][4];
int instructions[4][4];

void insertNode(vector <int>& word){
	int cur = 0;
	for(int letter : word){
		int& ind = T[cur].child[letter];
		if(ind == 0)
			ind = curNode++;
		cur = ind;
	}
	T[cur].isWord = 1;
}

void init(){
	ifstream fin("wDictionary.txt");
	vector <int> word;
	for(std::string line; std::getline(fin, line);)
		insertNode(greekFileToInt(line, word));
}

void readGrid(){
	cout << "Input Grid\n";
	for(int i = 0; i < ROWS; i++){
		cout << "Row " << i+1 << ": ";
		for(int j = 0; j < COLS; j++){
			char letter;
			cin >> letter;
			grid[i][j] = greekConsoleToInt(letter);
		}
	}
}

int dx[8]{0,1,1,1,0,-1,-1,-1};
int dy[8]{-1,-1,0,1,1,1,0,-1};
bool V[10][10];

typedef vector<pair<int,int>> Path;

unordered_map <string, Path> unordered_moves;
vector <pair<string, Path>> moves;
Path steps;

bool isValid(int x, int y){
	return 0 <= x && x < ROWS && 0 <= y && y < COLS;
}

string cur;

void dfs(int x, int y, int ind){
	steps.emplace_back(x,y);
	V[x][y] = 1;
	cur += ('A' + grid[x][y] - 1);
	if(T[ind].isWord && !unordered_moves.count(cur))
		unordered_moves[cur] = steps;
	
	for(int i = 0; i < 8; i++){
		int _x = x + dx[i];
		int _y = y + dy[i];
		if(isValid(_x,_y)){
			if(!V[_x][_y]){
				int nxt = T[ind].child[grid[_x][_y]]; 
				if(nxt != 0)
					dfs(_x,_y,nxt);
			}
		}
	}
	
	V[x][y] = 0;
	steps.pop_back();
	cur.pop_back();
}

void calcPaths(){
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++)
			dfs(i,j,T[0].child[grid[i][j]]);
	}
}

void orderPaths(){
	for(auto x : unordered_moves)
		moves.emplace_back(x.first, x.second);
	
	sort(moves.begin(), moves.end(), [](const pair<string, Path>& lhs,
		const pair<string, Path>& rhs){
		return lhs.first.size() > rhs.first.size();
	});
}

int cnt = 0;
void log(pair<string, Path> move){
	cout << "Path " << ++cnt << ":\n";
	int num = 1;
	
	print(move.first);
	
	for(pair <int,int> x : move.second)
		instructions[x.first][x.second] = num++;
		
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			cout << instructions[i][j] << " ";
			instructions[i][j] = 0;
		}
		cout << '\n';
	}
	cout << '\n';
}

void getCap(){
	int x;
	cin >> x;
	cout << "How many words to find? (enter -1 for max)\n";
	if(x != -1)
		cap = x;
}

int main(){
	init();
	readGrid();
	
	calcPaths();
	orderPaths();
	
	getGridPos();
	getCap();
	
	for(int i = 0; i < min((int)moves.size(), cap); i++){
		auto move = moves[i];
		log(move);
		inputWord(move.second);
	}
}

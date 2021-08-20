#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "encoder.cpp"
#include "automate.cpp"
using namespace std;

struct Node{
	unordered_map <int,int> child; 
	bool isWord;
};

int curNode = 1;
Node T[4000000];

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
/*DEBUG
vector <int> _cur;
void dfsDbg(int src){
	if(T[src].isWord){
		for(int x : _cur)
			cout << x << " ";
		cout << "\n";
	}
	for(pair<int,int> x : T[src].child){
		_cur.push_back(x.first);
		if(x.second != 0)
			dfsDbg(x.second);
		_cur.pop_back();
	}
}*/

void init(){
	ifstream fin("wDictionary.txt");
	for(std::string line; std::getline(fin, line);){
		int n = line.length();
		vector <int> word;
		word.clear();
		for(int i = 1; i < n; i += 2){
			int letter = (int)(line[i] + 112);
			word.push_back(letter);
		}
		insertNode(word);
		/*DEBUG
		cout << "[ ";
		for(int x : word)
			cout << x << " ";
		cout << "]\n";
		*/
	}
	//DEBUG
	//dfsDbg(0);
}

const int ROWS = 4, COLS = 4;
int grid[10][10];

void readGrid(){
	cout << "Input Grid\n";
	for(int i = 0; i < ROWS; i++){
		cout << "Row " << i+1 << ": ";
		for(int j = 0; j < COLS; j++){
			string letter;
			cin >> letter;
			grid[i][j] = letter[0] + 129;
			if(grid[i][j] >= 18)
				grid[i][j]++;
		}
	}
}

int dx[8]{0,1,1,1,0,-1,-1,-1};
int dy[8]{-1,-1,0,1,1,1,0,-1};
bool V[10][10];

bool isValid(int x, int y){
	return 0 <= x && x <= ROWS && 0 <= y && y <= COLS;
}

unordered_map <string, vector <pair<int,int>>> ans;
vector <pair<string,vector<pair<int,int>>>> moves;
vector <pair<int,int>> temp;

string cur;
void dfs(int x, int y, int ind){
	V[x][y] = 1;
	temp.emplace_back(x,y);
	cur += ('A' + grid[x][y] - 1);
	if(T[ind].isWord)
		ans[cur] = temp;
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
	temp.pop_back();
	cur.pop_back();
}

int step[10][10];

int main(){
	init();
	readGrid();
	getPosition();
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			dfs(i,j,T[0].child[grid[i][j]]);
		}
	}
	int cnt = 0;
	
	for(auto x : ans)
		moves.emplace_back(x.first, x.second);
	
	sort(moves.begin(), moves.end(), [](const pair<string,vector<pair<int,int>>>& lhs,
		const pair<string,vector<pair<int,int>>>& rhs){
		return lhs.first.size() > rhs.first.size();
	});
	
	for(auto y : moves){
		cout << "Path " << ++cnt << ":\n";
		//for(pair <int,int> x : y.second)
		//	cout << "[" << x.first+1 << " " << x.second+1 << "] "; 
		int num = 1;
		
		for(pair <int,int> x : y.second)
			step[x.first][x.second] = num++;
			
		for(int i = 0; i < ROWS; i++){
			for(int j = 0; j < COLS; j++){
				cout << step[i][j] << " ";
				step[i][j] = 0;
			}
			cout << "\n";
		}
			
		cout << "\n";
		print(y.first);
		cout << "\n";
		//Input to computer
		inputWord(y.second);
	}
}
/*
Á Â Á Í
Á Á Á Á
Â Á Í Á
Á Ð Ë Ï
*/

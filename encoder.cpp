#include <iostream>
#include <vector>
using namespace std;

void print(string s){
	for(char c : s)
		cout << (char)((c-'A') >= 18 ? c-'A'-129 : c-'A'-128);
	cout << '\n';
}

vector<int>& greekFileToInt(string line, vector <int>& word){
	word.clear();
	int n = line.length();
	for(int i = 1; i < n; i += 2){
		int letter = (int)(line[i] + 112);
		word.push_back(letter);
	}
	return word;
}

inline int greekConsoleToInt(char letter){
	int ans = letter + 129;
	if(ans >= 18)
		ans++;
	return ans;
}

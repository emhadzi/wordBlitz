#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map <char,int> letterCode;
string alphabet = "ABGDEZHUIKLMNJOPRSTYFXCV";

void initAlphabet(){
	for(int i = 0; i < (int)alphabet.length(); i++)
		letterCode[alphabet[i]] = i+1;
}

vector<int>& greekFileToInt(string line, vector <int>& word){
	word.clear();
	int n = line.length();
	for(int i = 1; i < n; i += 2){
		int letter = (int)(line[i] + 112);
		if(letter >= 19)
			letter--;
		word.push_back(letter);
	}
	return word;
}

inline int greekConsoleToInt(char letter){
	return letterCode[letter];
}

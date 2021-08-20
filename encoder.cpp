#include <iostream>
using namespace std;

void print(char x){
	if(x == 'A')
		cout << "\u0391";
	else if(x == 'B')
		cout << "\u0392";
	else if(x == 'C')
		cout << "\u0393";
	else if(x == 'D')
		cout << "\u0394";
	else if(x == 'E')
		cout << "\u0395";
	else if(x == 'F')
		cout << "\u0396";
	else if(x == 'G')
		cout << "\u0397";
	else if(x == 'H')
		cout << "\u0398";
	else if(x == 'I')
		cout << "\u0399";
	else if(x == 'J')
		cout << "\u039A";
	else if(x == 'K')
		cout << "\u039B";
	else if(x == 'L')
		cout << "\u039C";
	else if(x == 'M')
		cout << "\u039D";
	else if(x == 'N')
		cout << "\u039E";
	else if(x == 'O')
		cout << "\u039F";
	else if(x == 'P')
		cout << "\u03A0";
	else if(x == 'Q')
		cout << "\u03A1";
	else if(x == 'S')
		cout << "\u03A3";
	else if(x == 'T')
		cout << "\u03A4";
	else if(x == 'U')
		cout << "\u03A5";
	else if(x == 'V')
		cout << "\u03A6";
	else if(x == 'W')
		cout << "\u03A7";
	else if(x == 'X')
		cout << "\u03A8";
	else if(x == 'Y')
		cout << "\u03A9";
}

void print(string& str){
	for(int x : str)
		print(x);
}	


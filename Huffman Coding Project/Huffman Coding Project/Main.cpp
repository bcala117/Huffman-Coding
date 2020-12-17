#include"Huffman.h"
#include<iostream>
#include<fstream>

int main()
{
	
	Huffman a;
	//set to 26 for the letters in the alhpabet
	int frequency[26] = { 0 };
	string s;
	ofstream myfile;
	cout << "Enter string" << endl;
	getline(cin, s);

	//calling the buildTree function
	a.buildTree(s);
	

	return 0;
}
#include"Huffman.h"
#include<iostream>
#include<fstream>

int main()
{
	
	//vecotr used to read information from  the input files
	vector<char>input;

	//Huffman class object
	Huffman a;

	//set to 26 for the letters in the alhpabet
	int frequency[26] = { 0 };

	//initializing variables
	string fileName = "";
	int i = 0;

	cout << "Huffman Project" << endl << endl;
	//loops through all 20 files and send them into the algorithm
	while (i < 20)
	{
		//passing all of the file names through with an incrementing number to get the next input file 
		fileName = "input" + to_string(i) + ".txt";

		cout << "\n\n" << fileName << endl;

		//function call to read the specified file into the algorithm 
		a.readData(input, fileName);

		//calling the buildTree function
		a.buildTree(input, i);

		//this will output the size of the file before and after compression to the results.txt file
		result << "Compression Ratio: " << (float)product / previous << "\n\n";

		//increment i
		i++;

		//free memory
		input.clear();
	}

	return 0;
}
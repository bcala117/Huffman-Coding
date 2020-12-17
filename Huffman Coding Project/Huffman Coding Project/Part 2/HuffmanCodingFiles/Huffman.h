#pragma once
#include<queue>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<istream>
#include<iostream>
#include<ios>
#include<bitset>
#include<string>
#include<sstream>
using namespace std;

//unnamed namespace to house these variables
namespace
{
	int previous = 0, product = 0;
	ofstream result("result.txt", ios::app, ios::binary);
}


//Struct for the Huffman Node
struct h_Node
{
	//Character
	char character;

	//The frequency of the character 
	int frequency;

	//The left side of the node
	h_Node* left;

	//The right side of the node
	h_Node* right;

};

//Class that will define the way the priority queue is compared based on frequency 
class Comp
{
public:
	bool operator()(h_Node* h1, h_Node* h2);
};

//Class contianing the functions for the huffman coding algorithm
class Huffman
{
	
	
public:
	//declaration of functions for the Huffman coding
	
	h_Node* get(char character, int frequency, h_Node* left, h_Node* right);
	bool check(h_Node* root);
	void traverse(h_Node* root, string s, unordered_map<char, string>& huff);
	void decoding(h_Node* root, int& index, string s,ofstream&);
	void buildTree(vector<char> x, int i);
	void readData(vector<char>& in, string name);
	void compression(unordered_map<char, string>, string, vector<char>);
	int fileSize(string);
	string decompression(string);
};
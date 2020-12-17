#include"Huffman.h"
#include<iostream>


//Definition of the get function which will asssign a new node
h_Node* Huffman::get(char character, int frequency, h_Node* left, h_Node* right)
{
	h_Node* node = new h_Node();

	node->character = character;
	node->frequency = frequency;
	node->left = left;
	node->right = right;

	return node;
}

//Definition of function that checks if there is only 1 node in the tree
bool Huffman::check(h_Node* root)
{
	return root->left == nullptr && root->right == nullptr;
}

//definition of the traversal function that encodes the characters to a huffman value and stores them in an unordered map
void Huffman::traverse(h_Node* root, string s, unordered_map<char, string>& huff)
{
	//if a node is not found
	if (!root)
		return;
	//if a node is found
	if (check(root))
	{
		huff[root->character] = (s != "") ? s : "1";
	}

	traverse(root->left, s + "0", huff);
	traverse(root->right, s + "1", huff);
}

//Definition of the function that will decode the encoded string
void Huffman::decoding(h_Node* root, int& index, string s)
{
	//if a node is not found
	if (!root)
		return;

	//if a node is found
	if (check(root))
	{
		cout << root -> character;
		return;
	}
	index++;
	if (s[index] == '0')
		decoding(root->left, index, s);
	else
		decoding(root->right, index, s);
}

//Definition of function that will build the tree and decode the input
void Huffman::buildTree(string x)
{
	//If the string is empty do nothing
	if (x == "")
		return;

	//counts how many times each character appears and stores it in an unordered map
	unordered_map<char, int>frequency;
	for (char character : x)
		frequency[character]++;
	
	//creates a priority queue that will store the nodes
	priority_queue<h_Node*, vector<h_Node*>, Comp>pq;

	//creates a node for each character and stores puts it in the queue
	for (auto couple : frequency)
		pq.push(get(couple.first, couple.second, nullptr, nullptr));

	while (pq.size() != 1)
	{
		//Removes the two highest priority nodes
		h_Node* left = pq.top();
		pq.pop();
		h_Node* right = pq.top();
		pq.pop();

		int total = left->frequency + right->frequency;
		pq.push(get('\0', total, left, right));
	}

	h_Node* root = pq.top();

	//traverses the tree and stores the codes in the unordered map
	unordered_map<char, string>huff;
	traverse(root, "", huff);

	//Printing of data
	cout << "\nHuffman Codes: \n" << endl;

	for (auto couple : huff)
		cout << couple.first << " " << couple.second << endl;

	cout << "\nInputted String: " << x << endl;

	string s;
	for (char character : x)
		s += huff[character];
	
	cout << "\nThe encoded string is: " << s << endl;
	cout << "\nThe decoded string is: ";

	if (check(root))
	{
		while (root->frequency--)
			cout << root->character;
	}
	else
	{
		int index = -1;
		while (index < (int)s.size() - 1)
			decoding(root, index, s);
	}

}

//Definition of Comparison function
bool Comp::operator()(h_Node* h1, h_Node* h2)
{
	//The character with the highest priority will have the lowest frequency
	return h1->frequency > h2->frequency;
}
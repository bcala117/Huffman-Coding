#include"Huffman.h"



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

//Definition of the function that will decode the encoded string from the decompression function below
void Huffman::decoding(h_Node* root, int& index, string s, ofstream& decFile)
{
	//if a node is not found
	if (root == nullptr)
		return;

	//if a node is found
	if (!root->left && !root->right)
	{
		//writes value to decompression file 
		decFile.write((char*)&root->character, sizeof(char));
		return;
	}

	//incriments the index number
	index++;

	//try/catch statemnt to throw an exception for any errors in the process
	try {
		if (s[index] == '0')
		{
			decoding(root->left, index, s,decFile);
		}
			
		else
			decoding(root->right, index, s,decFile);
	}
	catch (exception e)
	{
		cout << "Exception" << endl;
	}
}

//Definition of function that will build the tree and decode the input
void Huffman::buildTree(vector<char> x, int i)
{

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

	cout << endl;
	//initializing output variable
	string output = ""
		;
	//just like in main it increments to go to the next file 
	output += "output" + to_string(i) + ".txt";
	
	//calss the compression function
	compression(huff, output, x);

	//calls decompression function to decompress the copmressed file 
	string s = decompression(output);

	string decoded;

	//increments to go to the next decoded file 
	decoded += "decoded" + to_string(i) + ".txt";
	

	ofstream d;
	d.open(decoded.c_str(), ios::out | ios::trunc);

	//decode the file
	int index = -1;

	while (index < (int)s.size() - 2) {
		decoding(root, index, s, d);
	}
	cout << endl;
}

//function to read in data from the input file 
void Huffman::readData(vector<char>& input, string name)
{

	ifstream readData(name.c_str(), ios::in);
	if (readData.is_open())
	{
		char character;
		while (readData.get(character))
		{
			input.push_back(character);
		}

		int space = fileSize(name);

		result << name << ": " << space << "\n";
		previous = space;

		readData.close();
	}
	else
		cout << "No file found" << endl;
}

//compresses the files and the encoded strings 
void Huffman::compression(unordered_map<char, string>huff, string name, vector<char>input)
{

	string info = "";

	for (char character : input)
		info += huff[character];

	//prints out what the encoded string is to the console window 
	cout << info << endl;
	ofstream o;
	o.open(name.c_str(), ios::out | ios::trunc);

	//takes the encoded string and divides it by 8 to change into ASCII values
	int eights = info.length() / 8;
	o.write((char*)&eights, sizeof(int));
	for (int i = 0; i < (info.length() / 8); i++)
	{
		char character = '\0';
		for (int j = 0; j < 8; j++)
		{
			character = character << 1;
			if (info[(i * 8) + j] == '0')
				character = character | 0;
			else
				character = character | 1;
		}
		o.write((char*)&character, sizeof(char));
	}
	if (info.length() % 8 != 0)
	{
		string remove = info.substr(eights * 8);
		for (int i = 0; i < remove.length(); i++)
		{

		}
	}

}

//gets the size of the file 
int Huffman::fileSize(string name)
{
	ifstream inData(name.c_str(), ios::binary);
	inData.seekg(0, ios::end);
	int fSize = inData.tellg();
	return fSize;
}

//definition of function to decompresss the string that will be decoded 
string Huffman::decompression(string name)
{
	int space = fileSize(name);
	result << name << ": " << space << endl;
	product = space;

	string info = "";
	ifstream output;
	output.open(name.c_str(), ios::in | ios::binary);
	int a;

	output.read((char*)&a, sizeof(int));
	for (int i = 0; i < a; i++)
	{
		char character;
		output.read((char*)&character, sizeof(char));
		for (int j = 0; j < 8; j++)
		{
			char temp = (char)128;
			if ((temp & character) == temp)
				info = info + "1";
			else
				info = info + "0";
			character = character << 1;
		}
	}
	char outchar;
	while (output.read((char*)&outchar, sizeof(char)))
		info = info + outchar;

	return info;
	output.close();
	
}

//Definition of Comparison function
bool Comp::operator()(h_Node* h1, h_Node* h2)
{
	//The character with the highest priority will have the lowest frequency
	return h1->frequency > h2->frequency;
}
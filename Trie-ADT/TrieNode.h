#ifndef TRIENODE_H
#define TRIENODE_H
#include <iostream>
using namespace std;

#define NUM_OF_ABC_LETTERS 26


typedef string KeyType;
typedef int DataType;

int convertLetterToNum(const char & c);
char convertNumToLetter(const int& index);

//Trie will consist of these nodes.
class TrieNode
{
private:
	char c;
	DataType count = 0; // Count the amount of words of thae key.
	TrieNode **children; //This is a potential array of pointers to TrieNodes. 

public:
	TrieNode* &getChild(const char & c); //function returns the child in the matching place.
	void deleteChild(const char& c); //Function deletes a child in the matching place.
	bool isNodeHasChildren() const; //Function checks if the object is a leaf.
	int countChildren() const;  //Function count the children.
	int getCount() const;
	TrieNode * makeLeaf(const char& c);

	bool isNodeHasChildChar(const char &c); //Function checks if node has children (leaf)
	bool isChildInCharCIsLeaf(const char & c);
	char getkey() const;

	void addToCount(const int& _count);
	char findFirstChildIndex(); //Helper function
	TrieNode(char c);
	~TrieNode();


};

#endif 
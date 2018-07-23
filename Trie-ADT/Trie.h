#ifndef TRIE_H
#define TRIE_H

#include <iostream>
using namespace std;
#include "TrieNode.h"

#define ROOT_CHAR '.' //In case the char in the root will be changed in the future.

typedef string KeyType; //needed because of double includes: circular dependency.
typedef int DataType;

class Trie
{
private:
	TrieNode *root;
public:
	friend int convertLetterToNum(const char & c); //Trie's helper, but also free for others to use.
	friend char convertNumToLetter(const int& index); //Trie's helper, but also free for others to use.

	Trie();
	~Trie();

	//Function gets a key and returns it exists in the Trie or returns the closest first key that is in the Trie. 
	KeyType approxFind(KeyType & Str);
	//Function insert a key to the Trie.
	void insert(KeyType keyToAdd);
	//Function finds a key in the trie. NOTE: approxFind only returns a string by the definition of the question! so this is needed.
	bool find(KeyType keyToFind, TrieNode * &pNodeRes);
	//Function gets a key and delete it.
	void deleteKey(KeyType keyToDelete);
	//Function checks if the trie is empty (used specifically in second phase of input).
	bool isEmpty();

private:
	void deleteTrieHelper(TrieNode* &pNode);//This function is destructor's right hand.
	void bigToLowerCaseLetter(KeyType & key) const; //"helper" function	
	bool deleteKeyHelper(TrieNode* pNode, KeyType keyToDel, int level, const int &keyToDelLen); //Helper function for deleteKey
};


#endif 
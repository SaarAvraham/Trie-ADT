#include <iostream>
using namespace std;
#include "Trie.h"


Trie::Trie()
{
	root = new TrieNode(ROOT_CHAR);
}

Trie::~Trie()
{
	deleteTrieHelper(root);
	delete root;
}

void Trie::deleteTrieHelper(TrieNode *& pNode)
{
	char letter;

	if (pNode->isNodeHasChildren() == true)
	{
		for (int i = 0; i < NUM_OF_ABC_LETTERS; i++)
		{
			letter = convertNumToLetter(i);
			if (pNode->isNodeHasChildChar(letter) == true)
			{
				deleteTrieHelper(pNode->getChild(letter)); //We want to delete from the bottom so no child will be left behind.
				pNode->deleteChild(letter);
			}
		}
	}
}



void Trie::insert(KeyType keyToAdd)
{
	TrieNode* pNode;
	int i, keyToAddLen = keyToAdd.length();

	bigToLowerCaseLetter(keyToAdd);//making sure its lower case with letters only.
	pNode = root;

	for (i = 0; i < keyToAddLen; i++)
	{
		if (pNode->isNodeHasChildChar(keyToAdd[i]) == false)
			pNode->makeLeaf(keyToAdd[i]);
		pNode = pNode->getChild(keyToAdd[i]);

	}
	pNode->addToCount(+1);
}

void Trie::bigToLowerCaseLetter(KeyType & key) const
{
	KeyType lowerCaseKey;
	int keyLen = key.size();

	for (int i = 0; i < keyLen; i++)
	{
		if ((key[i] >= 'A') && (key[i] <= 'Z'))
		{
			lowerCaseKey.push_back((char)key[i] - 'A' + 'a');
		}
		else if ((key[i] >= 'a') && (key[i] <= 'z'))
		{
			lowerCaseKey.push_back((char)key[i]);
		}
	}
	key = lowerCaseKey;
}


bool Trie::find(KeyType keyToFind, TrieNode * &pNodeRes)
{
	pNodeRes = nullptr;
	TrieNode* pNode = root;
	bigToLowerCaseLetter(keyToFind);
	int i, keyToFindLen = keyToFind.length();

	for (i = 0; i < keyToFindLen; i++)
	{
		if (pNode->isNodeHasChildChar(keyToFind[i]) == true)
			pNode = pNode->getChild(keyToFind[i]);
		else return false;
	}
	if (pNode->getCount() != 0) //Just because the letter exist, doesn't mean the word exist.
	{
		pNodeRes = pNode;
		return true;
	}
	else return false;
}

string Trie::approxFind(KeyType & Str)
{
	char letter;
	bigToLowerCaseLetter(Str);
	TrieNode* pNode = root;
	bool mutualStop = true, stop = false; //we assume we will find, untill we don't.
	int i, keyToFindLen = Str.length();
	string strApprox;

	for (i = 0; i < keyToFindLen && mutualStop == true; i++)
	{
		if (pNode->isNodeHasChildChar(Str[i]) == true)
		{
			if (pNode->isChildInCharCIsLeaf(Str[i]) == true) //is leaf
			{
				if (pNode->getChild(Str[i])->getkey() == Str[i])
					strApprox.push_back(Str[i]);
				return strApprox; //it's a leaf so there's no further nodes, it's what we should return.
			}
			else if (pNode->getChild(Str[i]) != nullptr)//if there's no leaf, then there could be a node.
			{
				if (pNode->getChild(Str[i])->getkey() == Str[i])
				{
					strApprox.push_back(Str[i]);
					if (i + 1 == keyToFindLen&& pNode->getChild(Str[i])->getCount() != 0)
						return Str;
					pNode = pNode->getChild(Str[i]);
				}
				else mutualStop = false;
			}
			else mutualStop = false;//no leaf, no node: we should stop here.
		}
		else mutualStop = false;
	}

	if (pNode->getCount() != 0) //if the count is not 0, it means we reached the first matching approx word.
		return strApprox;

	while (stop == false) //we need to look for the first alphabet word in the Trie.
	{
		if (pNode != nullptr)
		{
			if (pNode->isNodeHasChildren() == true)
				letter = pNode->findFirstChildIndex();//now we look for the first existing child from the left side of the array.
		}
		if (pNode->isChildInCharCIsLeaf(letter) == true && stop == false)
		{
			strApprox.push_back(pNode->getChild(letter)->getkey());
			return strApprox; //it's a leaf so there's no further nodes, it's what we should return.
		}
		else if (pNode->isNodeHasChildChar(letter) && stop == false)//if there's no leaf, then there could be a node.
		{
			strApprox.push_back(pNode->getChild(letter)->getkey());
			if (pNode->getChild(letter)->getCount() != 0)
				return strApprox;
			pNode = pNode->getChild(letter);
		}
		else stop = true;
		//no leaf, no node: we should stop here.

	}
}

int convertLetterToNum(const char & c)
{
	return (int)c - 'a';
}

char convertNumToLetter(const int & index)
{
	return (char)((char)index + 'a');
}


void Trie::deleteKey(KeyType keyToDelete)
{
	int keyToDelLen = keyToDelete.length();

	bigToLowerCaseLetter(keyToDelete);
	deleteKeyHelper(root, keyToDelete, 0, keyToDelLen);
	//print ERROR if necessary. 
}

bool Trie::isEmpty()
{
	if (root->isNodeHasChildren() == true)
		return false;
	else return true;
}


bool Trie::deleteKeyHelper(TrieNode* pNode, KeyType keyToDel, int level, const int &keyToDelLen)
{
	bool del;

	if (pNode != nullptr)
	{
		if (keyToDelLen == level)//This is the base case 
		{
			if (pNode != nullptr)
			{
				pNode->addToCount(-1); //We delete the instance of the word.
				if (pNode->isNodeHasChildren() == false && pNode->getCount() == 0) //Check if node should be removed.
				{
					return true;
				}
				else return false;
			}
			else return false;
		}
		else
		{
			del = deleteKeyHelper(pNode->getChild(keyToDel[level]), keyToDel, level + 1, keyToDelLen); //Recursive call
			if (del == true)
			{
				pNode->deleteChild(keyToDel[level]);
				return (pNode->isNodeHasChildren() == false && pNode->getCount() == 0); //we returns whether the node has children so we know if delete is necessary.
			}
		}
	}
	return false;
}


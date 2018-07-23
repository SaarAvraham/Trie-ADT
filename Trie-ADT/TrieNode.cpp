#include "TrieNode.h"
#include "Trie.h"
#include <assert.h>


TrieNode*& TrieNode::getChild(const char &c)
{
	int index = convertLetterToNum(c);

	return children[index];
}

void TrieNode::deleteChild(const char & c)
{
	char letter = c;
	int index = convertLetterToNum(c);

	if (this->isNodeHasChildren() == true)//Check if he's a leaf.
	{
		if (this->isNodeHasChildChar(c) == true)//Check if he has the mentioned child
		{
			if (this->getChild(c)->isNodeHasChildren() == false)//We don't want to delete a child with children.
			{
				delete children[index];
				children[index] = nullptr;

				if (this->countChildren() == 0)
				{
					delete[] children;
					children = nullptr;
				}
			}
		}
	}
	else assert(0);
}

bool TrieNode::isNodeHasChildren() const
{
	if (this->children != nullptr)
		return true;
	return false;
}

int TrieNode::countChildren() const
{
	int count = 0;

	for (int i = 0; i < NUM_OF_ABC_LETTERS; i++)
	{
		if (this->children[i] != nullptr)
			count++;
	}
	return count;
}

int TrieNode::getCount() const
{
	return this->count;
}

char TrieNode::findFirstChildIndex()
{
	assert((this->isNodeHasChildren()));
	int index;

	for (index = 0; index < NUM_OF_ABC_LETTERS; index++)
	{
		if (this->children[index] != NULL)
			return convertNumToLetter(index);
	}
}


char TrieNode::getkey() const
{
	return this->c;
}

void TrieNode::addToCount(const int & _count)
{
	count += _count;
}

TrieNode::TrieNode(char c)
{
	children = nullptr;
	this->c = c;
}



TrieNode::~TrieNode()
{
	if (this->isNodeHasChildren() == false)
	{
		delete[] children;
	}
}



TrieNode * TrieNode::makeLeaf(const char& c)
{
	char charOfChild = c;
	int index = convertLetterToNum(c);

	if (this->children == nullptr)  //This node is not ready yet for children.
	{
		this->children = new TrieNode*[NUM_OF_ABC_LETTERS];
		for (size_t i = 0; i < NUM_OF_ABC_LETTERS; i++)
			this->children[i] = nullptr;
	}
	this->children[index] = new TrieNode(charOfChild);
	return this->children[index];
}

bool TrieNode::isNodeHasChildChar(const char &c)
{
	char letter = c;

	if (this->isNodeHasChildren() == false)
		return false;
	else
	{
		if (this->getChild(letter) == false)
			return false;
		else return true;
	}
}

bool TrieNode::isChildInCharCIsLeaf(const char & c)
{
	char letter = c;

	if (this->getChild(letter)->isNodeHasChildren() == false)
		return true;
	else return false;
}

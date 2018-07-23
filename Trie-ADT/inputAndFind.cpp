#include <iostream>
#include <string>
#include "Trie.h"
#include "inputAndFind.h"
using namespace std;

bool hasLetters(const string& str)
{
	int i, wordLen = str.length();

	for (i = 0; i < wordLen; i++)
	{
		if (isLetter(str[i]) == true)
			return true;
	}
	return false;
}

bool isLetter(const char & c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
	else return false;
}

void getIntialInput(Trie& trie)
{
	int writeIndex;
	string text;
	char word[MAX_WORD_LEN];
	int textLen, i;
	char currLetter;

	bool stop = false;
	while (stop == false)
	{
		getline(std::cin, text, END_OF_ROW_DELIMITER);
		i = 0;
		textLen = text.length();
		if (text != END_OF_INPUT)//it means it's a legitimate line
		{
			writeIndex = 0;
			while (i < textLen)
			{
				currLetter = text[i];
				if (isLetter(currLetter) == true)
				{
					word[writeIndex] = currLetter;
					writeIndex++;
				}
				else if (writeIndex > 0)
				{
					word[writeIndex] = '\0';
					trie.insert((string)word);
					writeIndex = 0;
				}

				if (writeIndex > 0 && i + 1 == textLen)
				{
					word[writeIndex] = '\0';
					trie.insert((string)word);
					writeIndex = 0;
				}
				i++;
			}
		}
		else stop = true;
	}
}

void getSecondInputToFind(Trie & trie)
{
	TrieNode* pNode;
	string word, res;
	int wordCount;
	bool isTrieEmpty = trie.isEmpty();
	bool stop = false;

	while (stop == false)
	{
		getline(std::cin, word, END_OF_ROW_DELIMITER);

		while (hasLetters(word) == false && word != END_OF_INPUT)//We ignore "words" that don't have letters at all.
			getline(std::cin, word, END_OF_ROW_DELIMITER);

		if (word != END_OF_INPUT && isTrieEmpty == false)//Legitimate line and the trie is not empty.
		{
			res = trie.approxFind(word); //approxFind only returns a string by the definetion of the question!
			if (res == word)
			{
				trie.find(word, pNode); //approxFind only returns a string by the definetion of the question!

				if (pNode != nullptr)//Just in case.. To avoid segmentation faults.
				{
					wordCount = pNode->getCount();
					cout << wordCount << endl;
					trie.deleteKey(word);
				}
			}
			else //"approx" word was found.
			{
				cout << "Did you mean " << res << "?" << endl;
			}
		}
		else stop = true;
		isTrieEmpty = trie.isEmpty(); //if the trie is empty, there will could be a problem.
	}
	if (isTrieEmpty == true && word != END_OF_INPUT)
		cout << "Trie is empty! \n";
}

#ifndef INPUTANDFIND_H
#define INPUTANDFIND_H

#include"Trie.h"
#include <string>
#include <iostream>

//In case it will be changed in the futrue, the programmer\user will only need to change the end of input or the delimiter here.
#define END_OF_INPUT "." 
#define END_OF_ROW_DELIMITER '\n'

using namespace std;

typedef string KeyType; //needed because of double includes: circular dependency.
typedef int DataType;

#define MAX_WORD_LEN 64 

//This function checks if the string 'str' has letters
bool hasLetters(const string& str);

//This function checks if the char 'c' is a letter
bool isLetter(const char & c);

//Function handles the first phase.
void getIntialInput(Trie& trie);

//Function handles the second phase.
void getSecondInputToFind(Trie& trie);

#endif  
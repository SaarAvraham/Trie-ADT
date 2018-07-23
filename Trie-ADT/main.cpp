#include <iostream>
using namespace std;
#include <string>
#include "Trie.h"
#include "inputAndFind.h"



int main()
{
	Trie trie;
	getIntialInput(trie); //Phase 1 in the program.
	getSecondInputToFind(trie); //Phase 2 in the program.
	return 0;
}
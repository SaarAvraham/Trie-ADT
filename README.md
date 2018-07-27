Data structures
Programming Exercise

Saar Avraham, ID: 203436639

Semester: A (2018)

Visual stuidio 2015

The trie structrue:

The trie consists of TrieNodes which each of them has a pointer to pointer named "children" (**TrieNode) which will point to
an array of pointers if it's not a leaf. So Leaf's "children" will be nullptr (no allocation at all). 
The number of letter in the alphabet it 26, so each node which is not leaf will contain an array of pointers to TrieNodes with size of 26.
Of Course, the array size is a constant named "NUM_OF_ABC_LETTERS".
Of course, TrieNodes have a count integer as well.


Notes:
1) In phase two of the input, the words that will be taken care of are only ones with letters. 
Also, if the program's input is: "A-my", it will be transformed to "amy" with only low case letters, and then taken care of.
(This is what was defined in the question and in the Q&A section). 

2) If the longest key route legnth in the trie mutual with the input is 0, the Trie will return the first word in the alphabet of the Trie.
(This is what was defined in the question when longest key route legnth=0). 

3) When the Trie is empty, if the user will input a word in phase two, the program will print "Trie is empty!".

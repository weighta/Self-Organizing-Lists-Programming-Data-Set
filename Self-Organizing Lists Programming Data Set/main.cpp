//Alexander P. Weight
//Professor Jason Christian
//CSIS215: Algorithms and Data Structures (D02)
//May 10, 2024

#include <iostream>
#include "SelfOrderedList.h"
#include <fstream>

std::fstream input;
int inputSize;
int wordInputSize;

void openFile() { ///Open the file "test.txt"
	char filename[] = "test.txt";
	input.open(filename, std::fstream::in | std::fstream::binary);

	input.seekg(0, input.end); //seek the entire file
	inputSize = input.tellg(); //capture the full size for future overflow checking
}

void copyBufferNulled(char* wordBuffer, char* buffer, int n) {
	int a = 0;
	char wasLastSpace = 0;
	for (int i = 0; i < n; i++) {
		if (buffer[i] != ' ') {
			wordBuffer[a++] = buffer[i];
			wasLastSpace = 0;
		}
		else {
			if (!wasLastSpace) {
				wasLastSpace = 1;
				a++;
			}
		}
	}
	wordInputSize = a;
}


void charTest0() {
	SelfOrderedList<char>* list[3];

	for (int i = 0; i < 3; i++) {
		list[i] = new SelfOrderedList<char>(i);
	}

	char chars[] = "A B C D E F G H";
	int n = sizeof(chars) >> 1;

	sayl("Initializing Char Test... A B C D E F G H\n");

	for (int i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			sayl("Count:");
			break;
		case 1:
			sayl("Move-To-Front:")
				break;
		case 2:
			sayl("Transpose:");
			break;
		}
		for (int j = 0; j < n; j++) {
			char c = chars[(j << 1)];
			list[i]->find(c);
		}

		list[i]->printlist();
	}

}

void charTest1() {
	SelfOrderedList<char>* list[3];

	for (int i = 0; i < 3; i++) {
		list[i] = new SelfOrderedList<char>(i);
	}

	char chars[] = "F D F G E G F A D F G E H";
	int n = sizeof(chars) >> 1;

	sayl("Initializing Char Test... F D F G E G F A D F G E H\n");
	
	for (int i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			sayl("Count:");
			break;
		case 1:
			sayl("Move-To-Front:")
				break;
		case 2:
			sayl("Transpose:");
			break;
		}
		for (int j = 0; j < n; j++) {
			char c = chars[(j << 1)];
			list[i]->find(c);
		}

		list[i]->printlist();
	}
}

void wordTest() {
	sayl("Initializing Word Test...\n");

	SelfOrderedList<char*>* list[3];

	for (int i = 0; i < 3; i++) {
		list[i] = new SelfOrderedList<char*>(i);
	}

	char buffer[0xFFF];
	char wordBuffer[0xFFF];
	memset(wordBuffer, 0x0, 0xFFF);

	openFile();

	input.seekg(0, input.beg); //seek the data
	input.read(buffer, inputSize); //read and assign the data to block

	copyBufferNulled(wordBuffer, buffer, inputSize);

	for (int i = 0; i < 3; i++) { //Go to 3 since there are 3 heuristics to test
		switch (i) {
		case 0:
			sayl("Count:");
			break;
		case 1:
			sayl("Move-To-Front:")
				break;
		case 2:
			sayl("Transpose:");
			break;
		}
		char newWord = 1;
		for (int j = 0; j < wordInputSize; j++) {
			if (newWord) {
				char* word = &wordBuffer[j];
				list[i]->find(word);
				newWord = 0;
			}
			if (wordBuffer[j] == 0) {
				newWord = 1;
			}
		}
		list[i]->printlist(10);
	}
}

int main() {
	charTest0();
	charTest1();
	wordTest();
	return 0;
}
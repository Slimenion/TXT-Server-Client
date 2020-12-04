#ifndef FUNC_H
#define FUNC_H
#include <string>
#include <fstream>
using namespace std;

#define Password PASS 
#define Login LOG

int Find_Split(string word) {
	int k = 0;
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] == ' ') return i;
	}
}

int Find_Size(string DATA) {
	int size;
	ifstream CON;
	CON.open(DATA);
	CON.seekg(0, std::ios::end);
	size = CON.tellg();
	CON.close();
	return size;
}
#endif


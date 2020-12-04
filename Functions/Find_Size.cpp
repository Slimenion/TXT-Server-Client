#include <string>
#include <fstream>
using namespace std;

int Find_Size(string DATA) {
	int size;
	ifstream CON;
	CON.open(DATA);
	CON.seekg(0, std::ios::end);
	size = CON.tellg();
	CON.close();
	return size;
}
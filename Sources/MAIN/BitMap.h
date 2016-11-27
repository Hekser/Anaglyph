#pragma once
#include <vector>
#include <string>

using namespace std;

class BitMap
{
public:
	BitMap(string);
	~BitMap();
	int getSize();
	int getWidth();
	int getHeight();
	unsigned char * getData();
	unsigned char * getSplitData(int);
	unsigned int getSplitDataHeight(int);
	void saveToFile(string);
	void splitInto(unsigned);
private:
	int width;
	int height;
	int size;
	unsigned char *data;
	unsigned char *info;
	vector <unsigned char *> splitData;
	vector <int> splitDataHeight;
};
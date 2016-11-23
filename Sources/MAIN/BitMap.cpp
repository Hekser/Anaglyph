#include "BitMap.h"

BitMap::BitMap(string path) :
	data(NULL),
	info(NULL)
{
	FILE* f = fopen(path.data(), "rb");
	info = new unsigned char[54];
	fread(info, sizeof(unsigned char), 54, f);		// 54-byte header

	width = *(int*)&info[18];
	height = *(int*)&info[22];
	size = *(int*)&info[34];

	data = new unsigned char[size];					// 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f);	// read bmp pixels
	fclose(f);
}

BitMap::~BitMap() {
	delete this->data;
	this->data = NULL;
	delete this->info;
	this->info = NULL;
	this->splitData.clear();
}

int BitMap::getSize() {
	return this->size;
}

int BitMap::getWidth() {
	return this->width;
}

int BitMap::getHeight() {
	return this->height;
}

unsigned char * BitMap::getData() {
	return this->data;
}

unsigned char * BitMap::getSplitData(int index) {
	return this->splitData[index];
}

unsigned int BitMap::getSplitDataHeight(int index) {
	return this->splitDataHeight[index];
}

void BitMap::saveToFile(string path) {
	FILE* f = fopen(path.data(), "wb");
	fwrite(info, sizeof(unsigned char), 54, f);
	fwrite(data, sizeof(unsigned char), size, f);
	fclose(f);
}

void BitMap::splitInto(unsigned concurentThreadsSupported) {

	int pieceHeight = (int)(height / concurentThreadsSupported);
	splitData.push_back(data);
	splitDataHeight.push_back(height - pieceHeight * (concurentThreadsSupported - 1));

	unsigned char pad = 0;

	if ((width * 3) % 4 != 0) {
		pad = 4 - ((width * 3) % 4);
	}

	for (unsigned i = 1; i < concurentThreadsSupported; ++i) {
		splitData.push_back(splitData[i - 1] + splitDataHeight[i - 1] * width * 3 + splitDataHeight[i - 1] * pad);
		splitDataHeight.push_back(pieceHeight);
	}
}